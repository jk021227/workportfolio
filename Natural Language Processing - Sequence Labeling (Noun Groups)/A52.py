from typing import TypedDict, Union, List
import nltk
from fastprogress.fastprogress import progress_bar

stemmer = nltk.stem.SnowballStemmer('english')


class TokenAttributes(TypedDict):
    word: str
    pos: str
    capitalized: bool
    tag: Union[str, None]


def parse_input(input_filepath: str) -> List[Union[List[TokenAttributes], None]]:
    with open(input_filepath, "r") as f:
        lines = f.readlines()

    sentences: List[Union[List[TokenAttributes], None]] = []
    last_sentence: List[TokenAttributes] = []
    total_lines = len(lines)

    for index, line in enumerate(lines, start=1):
        line = line.strip()
        token_data = line.split("\t")
        if len(token_data) >= 2:
            word = TokenAttributes(
                word=token_data[0].strip(),
                pos=token_data[1].strip(),
                capitalized=token_data[0][0].isupper(),
                tag=token_data[2].strip() if len(token_data) >= 3 else None
            )
            last_sentence.append(word)
        else:
            if last_sentence:
                sentences.append(last_sentence)
                last_sentence = []
            sentences.append(None)

        if index % 1000 == 0:
            print(f"Parsed {index}/{total_lines} lines...")

    if last_sentence:
        sentences.append(last_sentence)

    return sentences


class TokenFeatures(TypedDict):
    # (the same as before, I won't repeat it for brevity)


def get_word_features(sentence: List[TokenAttributes]) -> List[TokenFeatures]:
    token_features_list = []
    sentence_len = len(sentence)

    prev_word, prev_2_word, current_word, next_word, next_2_word = [None] * 5

    stems = [stemmer.stem(word["word"]) if word else None for word in sentence]

    for i in range(sentence_len):

        prev_2_word, prev_word, current_word, next_word, next_2_word = \
        prev_word, current_word, sentence[i], \
        sentence[i + 1] if i + 1 < sentence_len else None, \
        sentence[i + 2] if i + 2 < sentence_len else None

        word_str = current_word["word"]
        word_stem = stems[i]
        word_pos = current_word["pos"]
        word_capitalized = current_word["capitalized"]
        word_tag = current_word["tag"]

        token_features = TokenFeatures(
            # (the same as before, I won't repeat it for brevity)
        )

        token_features_list.append(token_features)

    return token_features_list


def process_file(source_filepath: str, destination_filepath: str):
    sentences = parse_input(source_filepath)

    with open(destination_filepath, "w") as f:
        first_sentence = True
        for sentence in progress_bar(sentences):
            if sentence is None:
                if first_sentence or prev_sentence_was_not_none:
                    f.write("\n")
                prev_sentence_was_not_none = False
            else:
                token_features = get_word_features(sentence)
                for token_feature in token_features:
                    token_feature_str_list = []
                    for key, value in token_feature.items():
                        if value is None or key == "word" or key == "tag":
                            continue
                        token_feature_str_list.append(f"{key.upper()}={value}")
                    token_feature_str_list.insert(0, token_feature["word"])
                    if token_feature["tag"] is not None:
                        token_feature_str_list.append(token_feature['tag'])
                    if not first_sentence:
                        f.write("\n")
                    else:
                        first_sentence = False
                    f.write("\t".join(token_feature_str_list))
                prev_sentence_was_not_none = True

def main():
    process_file('WSJ_02-21.pos-chunk', 'training.feature')  
    process_file('WSJ_23.pos', 'test.feature') 

if __name__ == '__main__':
    main()
