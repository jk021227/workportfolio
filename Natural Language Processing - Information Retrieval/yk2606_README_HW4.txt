How to Run the Code:
1. Ensure that Python is installed on your machine.
2. Ensure you have the necessary libraries installed. If not, install them using pip.
3. Place the 'cran.qry', 'cran.all.1400', and 'stop_list.py' in the same directory as the python program.
4. Run the script using the command: python3 IR3.py
5. It will take about 10 seconds to run & terminate and you will have an output file in the same directory named 'output.txt'


Imported Libraries & What Each Does:
- 'math': Provides mathematical functions. Used for operations like logarithm and square root in TF-IDF computation and cosine similarity.
- 're': Allows using regular expressions. Used for tokenizing text by removing punctuations and numbers.
- 'collections': Provides alternative container datatypes. 'defaultdict' and 'Counter' are used to simplify the management of nested dictionaries and counting occurrences of terms.
- 'nltk.stem.PorterStemmer': Provides the Porter stemming algorithm, which is a process for removing the commoner morphological and inflexional endings from words.
- 'stop_list': Custom module containing a list of closed class stop words. Used to filter out common words that don't carry significant meaning.


Further Explanation of Code: 
process_data(file_path):
- This function preprocesses and tokenizes the dataset.
- It reads from the file, splits lines into terms, filters out stop words, stems the terms, and returns a dataset in the form of a dictionary.

compute_tf_idf_values(dataset, total_entries):
- Computes the Term Frequency-Inverse Document Frequency (TF-IDF) for each term in the dataset.
- Uses the `Counter` to efficiently count term occurrences and calculates TF and IDF scores for terms.
- Returns a nested dictionary containing TF-IDF scores for terms in each document or query.

compute_similarity(query_values, doc_values):
- Computes the cosine similarity between each query and document using their TF-IDF vectors.
- Returns a nested dictionary containing similarity scores for each query-document pair.

write_output_to_file(similarity_scores):
- Writes the computed similarity scores to an output file.
- Each line in the output file is in the format '<query_id> <document_id> <score>'.
