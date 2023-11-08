**Running the Code**

To run my code, follow the steps below:

1. Ensure you have all the required modules and helper functions defined and accessible(same directory etc.).
2. Open your terminal or command prompt.
3. Navigate to the directory where your script is located. (e.g. cd Desktop cd etc.)
4. Run the script by typing the following line in your terminal:
python [training/dev_file_combined] [test_file]

Replace `[training/dev_file_combined]` with the path to your file which has combined the training & development file and `[test_file]` with the path to your test file(the file you want to tag).

**Handling Out-of-Vocabulary (OOV) Words**
For this code, OOV words are handled using a custom function, `OOV_tag(word, index, pos_keys)`. Here's how it operates:

1. **Numeric Words**: If the OOV word is numeric (either an integer or a float), it's tagged as 'CD' (Cardinal Number).
  
2. **Pattern Matching**: Several common patterns are checked in the OOV word:
   - Words ending with 'age' and starting with a lowercase letter are inferred as Nouns ('NN').
   - Presence of 'able' in the word indicates an Adjective ('JJ').
   - Presence of a hyphen in the word also suggests it's an Adjective ('JJ').
   - Words ending in 'ed', 'ly', 'er', 'est', and 'ing' are tagged as 'VBD' (Verb, Past Tense), 'RB' (Adverb), 'JJR' (Adjective, Comparative), 'JJS' (Adjective, Superlative), and 'VBG' (Verb, Gerund or Present Participle) respectively.

3. **Special Cases**: If the word is tagged as 'VBG', an additional tag 'VB' (Verb, Base Form) is also considered for the word.

4. **Default Tagging**: If no patterns match, by default, the word is tagged as a Noun ('NN').

5. **Proper Nouns**: For words that start with an uppercase letter and are not the first word in the sentence, the function checks:
   - If they end with 's', they are tagged as 'NNPS' (Proper Noun, Plural).
   - Otherwise, they are tagged as 'NNP' (Proper Noun, Singular).
   - Additionally, words ending with 's' might also be 'NNS' (Noun, Plural).

The goal of this function is to utilize common patterns and structures in the English language to make educated guesses about the POS of OOV words. I took on a heuristic-based approach as using a constant likelihood did not seem to work the best with accuracy. It was a more practical way of dealing with unseen words without resorting to more complex solutions. I also used "https://aclanthology.org/J93-2004.pdf" when creating the function if statement specifications.