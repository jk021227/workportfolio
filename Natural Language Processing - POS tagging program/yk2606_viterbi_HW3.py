import helpers
from sys import argv, exit

def viterbi(training, test_file): 
    corpus_list = helpers.text_list(training)
    corpus_dictionary = helpers.corpus_dictionary(training)
    keys = helpers.key_list(corpus_dictionary)
    prior_probabilities_table = helpers.transition_table(corpus_dictionary,corpus_list)
    word_dictionary = helpers.word_dic(corpus_list,keys)
    words = helpers.key_list(word_dictionary)
    likelihood_table = helpers.word_freq(corpus_dictionary,word_dictionary)
    sentences = helpers.text_list_2(test_file)

    new_sentences = []
    for sentence in sentences:
        trans = helpers.sentence_tagging(sentence, keys, words, likelihood_table)
        s_pos = helpers.sentence_pos(trans)
        transition_table = helpers.transition_probabilities(trans, s_pos, prior_probabilities_table, keys)
        observed_like = helpers.observed_likelihoods(sentence, s_pos, trans, likelihood_table, words, keys)
        vit_sent = helpers.viterbi_algo(observed_like, sentence, s_pos, transition_table)
        new_sentences.append(vit_sent[:-1])  # Remove the last item of vit_sent here

    return new_sentences

def output_file(tags, write_file):
    with open(write_file, 'w') as out:
        for sentence in tags:
            for word, tag in sentence:
                out.write(f"{word}\t{tag}\n")
            out.write("\n")

def main():
    if len(argv) != 3:
        print("Please provide two arguments: file1, file2")
        exit()

    training = argv[1]
    run_file = argv[2]
    out = "submission.pos"
    tags = viterbi(training, run_file)
    output_file(tags, out)

if __name__ == "__main__":
    main()