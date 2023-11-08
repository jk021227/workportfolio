import math
import re
from collections import defaultdict, Counter
from nltk.stem import PorterStemmer
from stop_list import closed_class_stop_words

# this function will compute cosine similarity between queries & documents
def compute_similarity(query_values, doc_values):
    sim_scores = defaultdict(dict) # initializing a dictionary to store similarity scores

    for q_id, q_vector in query_values.items(): # looping through each query & document to compute similarity scores
        for doc_id, doc_vector in doc_values.items():
            intersection_terms = set(q_vector.keys()) & set(doc_vector.keys()) # finding terms that are present in both query & document, can discard terms not in these vectors as they will have mutiplication of 0
            numerator = sum([q_vector[term] * doc_vector[term] for term in intersection_terms]) # computing the numerator of the cosine similarity formula

            # computing the denominators for the cosine similarity formula
            sum_query = sum([q_vector[term]**2 for term in q_vector])
            sum_doc = sum([doc_vector[term]**2 for term in doc_vector])
            denominator = math.sqrt(sum_query) * math.sqrt(sum_doc)

            # computing the cosine similarity score & storing it
            if denominator:
                sim_scores[q_id][doc_id] = float(numerator) / denominator

    for q_id in sim_scores: # sorting the similarity scores for each query
        sim_scores[q_id] = dict(sorted(sim_scores[q_id].items(), key=lambda item: item[1], reverse=True))

    return sim_scores # returning the sorted similarity scores

# this function will compute the TF-IDF values for each term in the dataset
def compute_tf_idf_values(dataset, total_entries):
    term_idf = {} # initializing dictionaries for IDF values and TF-IDF values
    tfidf_values = defaultdict(dict)
    all_terms = [term for doc in dataset.values() for term in doc] # getting a list of all terms in the dataset
    
    for term in set(all_terms): # computing the IDF for each unique term in the dataset
        term_idf[term] = math.log(total_entries / sum(1 for doc in dataset.values() if term in doc))

    for entry_id, terms in dataset.items(): # computing the TF-IDF for each term in each query
        term_counts = Counter(terms) # getting the term frequencies using the Counter
        total_terms = len(terms)
        for term, count in term_counts.items():
            tf = count / total_terms
            tfidf_values[entry_id][term] = tf * term_idf[term]

    return tfidf_values # returning the computed TF-IDF values

# this function will preprocess & tokenize the dataset
def process_data(file_path):
    dataset = {} # initializing an empty dictionary to store processed data
    ps = PorterStemmer() # instantiating a Porter stemmer - stemmers ensure that stem wrods are grouped

    with open(file_path, 'r') as file: # opening the file for reading
        entry_id = 0 # initializing the entry ID & content flag
        content = False

        for line in file: # looping through each line in the file
            if '.I' in line: # if we encounter an '.I' line, it signifies ids for queries
                entry_id += 1
                content = False
            elif '.W' in line: # '.W' line indicates that the subsequent lines will contain the content
                content = True
                continue
            elif content: # processing the content
                cleaned_words = [word for word in re.split('\W|\d', line.strip().lower()) # tokenizing the line, filter out punctuation, numbers, and stop words, and convert to lowercase
                                 if word and word not in closed_class_stop_words]
                stemmed_words = [ps.stem(word) for word in cleaned_words] # stemming the words
                dataset[entry_id] = dataset.get(entry_id, []) + stemmed_words # updating the dataset with the processed terms
    
    return dataset # returning preprocessed dataset

# this function will write the similarity scores to the output file
def write_output_to_file(similarity_scores):
    with open('output.txt', 'w') as file:
        for query_id, docs in similarity_scores.items(): # looping through each query & its similarity scores with documents
            for doc_id, score in docs.items(): # writing each score to the file up to 6 decimal places
                file.write(f'{query_id} {doc_id} {score:.6f}\n')

if __name__ == "__main__":
    # preprocessing and tokenizing queries & documents
    queries = process_data('cran.qry')
    documents = process_data('cran.all.1400')

    # computing TF-IDF values for queries & documents
    query_tf_idf = compute_tf_idf_values(queries, len(queries))
    doc_tf_idf = compute_tf_idf_values(documents, len(documents))

    # computing similarity scores between queries & documents
    similarity_scores = compute_similarity(query_tf_idf, doc_tf_idf)
    # writing the computed similarity scores to output file
    write_output_to_file(similarity_scores)
