import numpy
import csv
import itertools


def text_list(filename): 
	tf = open(filename , 'r')

	sentence = []
	array = []
	count = 0
	for line in tf:
		l = line.split()
		if len(l) == 0:
			array.append(sentence) 
			sentence = [] 
		else:
			tags = (l[0],l[1]) 
			sentence.append(tags)
	return array 

def text_list_2(filename): #array of sentences
	tf = open(filename,'r') 
	sentence = [] 
	array = []
	for line in tf:
		l = line.split()
		if(len(l) == 0):
			array.append(sentence) 
			sentence = []
		else:
			tags = (l[0]) 
			sentence.append(tags) 
	return array

def corpus_dictionary(filename):
    """ Generates a dictionary with tags as keys and their frequencies as values. """
    dic = {}
    with open(filename, 'r') as tf:
        for line in tf:
            l = line.split()
            if len(l) == 2:
                dic[l[1]] = dic.get(l[1], 0) + 1
    return dic

def key_list(dic):
    """ Extracts the list of keys from a dictionary. """
    return list(dic.keys())

def isfloat(string):
    try:
        float(string)
        return True
    except ValueError:
        pass
    
    try:
        float(string.replace(',', ''))
        return True
    except ValueError:
        return False

def helper_transition(sentence, matrix, col_head, row_head):
    """ Updates the matrix based on sentence transitions. """
    this_sentence = [('','start')] + sentence + [('','end')]
    for i in range(len(this_sentence) - 1):
        matrix[row_head.index(this_sentence[i][1])][col_head.index(this_sentence[i+1][1])] += 1


def prior_probabilities(text_list, matrix, dic, list_2):
    """ Normalizes the matrix to make it represent probabilities. """
    for i, row in enumerate(matrix):
        if i == 0:
            matrix[i] = [value / len(text_list) for value in row]
        else:
            matrix[i] = [value / dic[list_2[i]] for value in row]

def transition_table(dic, text_list):   
	ls = list(dic.keys())  # Get keys from the dictionary and create column and row headers for the transition table.
	list1 = ls + ['end']  # columns represent "to" states, including an end state
	list2 = ['start'] + ls  # rows represent "from" states, starting from a start state

    # Initialize the transition table with zeros.
	table = numpy.zeros(shape=(len(list2), len(list1)))

    # Fill in the transition counts for each sentence in the text_list.
	for sentence in text_list:
		helper_transition(sentence, table, list1, list2)

    # Normalize the transition counts to calculate probabilities.
	prior_probabilities(text_list, table, dic, list2)

	return table

def word_dic(text_list, col_head):
    """ Creates a dictionary of words and their tag counts. """
    dic = {}
    for sentence in text_list:
        for word, pos in sentence:
            word = word.lower()
            dic.setdefault(word, [0] * len(col_head))[col_head.index(pos)] += 1
    return dic

def word_freq(pos_dic, word_dic):
    # Get word and POS keys directly from the dictionaries.
    word_keys = list(word_dic.keys())
    pos_keys = list(pos_dic.keys())

    # Initialize the likelihood matrix with zeros.
    table = numpy.zeros(shape=(len(word_keys), len(pos_keys)))

    # Fill the matrix by iterating over each word and its corresponding POS counts.
    for word_index, (word, tag_counts) in enumerate(word_dic.items()):
        for tag_index, tag_count in enumerate(tag_counts):
            table[word_index, tag_index] = float(tag_count) / float(pos_dic[pos_keys[tag_index]])
    return table

def OOV_tag(word, index, pos_keys):
	OOV_pos = []

	# Check for numeric
	if word.isnumeric() or isfloat(word):
		OOV_pos.append('CD')

	# Check for common word patterns
	patterns = [
		(word[0].islower() and word.endswith('age'), 'NN'),
		('able' in word, 'JJ'),
		('-' in word, 'JJ'),
		(word.endswith('ed'), 'VBD'),
		(word.endswith('ly'), 'RB'),
		(word.endswith('er'), 'JJR'),
		(word.endswith('est'), 'JJS'),
		(word.endswith('ing'), 'VBG')
	]

	for condition, tag in patterns:
		if condition and tag not in OOV_pos:
			OOV_pos.append(tag)

	# Special case for VB when VBG is inferred
	if 'VBG' in OOV_pos and 'VB' not in OOV_pos:
		OOV_pos.append('VB')

	# Default case
	if not OOV_pos:
		OOV_pos.append('NN')

	# Proper noun-related patterns
	if word[0].isupper() and index > 0:
		if word.endswith('s') and 'NNPS' not in OOV_pos:
			OOV_pos.append('NNPS')
		elif 'NNP' not in OOV_pos:
			OOV_pos.append('NNP')
		if word.endswith('s') and 'NNS' not in OOV_pos:
			OOV_pos.append('NNS')

	return OOV_pos

def sentence_tagging(sentence, pos_keys, word_keys, likelihood_table):
    pos_mappings = {}

    for idx, word in enumerate(sentence):
        try:
            word_index = word_keys.index(word.lower())
        except ValueError:
            word_index = -1

        # If the word exists in word_keys, get tags from likelihood table
        if word_index > -1:
            pos_mappings[idx] = [pos_keys[j] for j, likelihood in enumerate(likelihood_table[word_index]) if likelihood > 0]
        # If OOV, get tags using OOV_tag function
        else:
            pos_mappings[idx] = OOV_tag(word, idx, pos_keys)

    return pos_mappings


def sentence_pos(dic):
	pos_set = {pos for key in dic for pos in dic[key]}
	return list(pos_set)


def transition_probabilities(dic, pos_list, transition_table, pos_keys):
    # Define rows and columns for the new table and the original table.
    rows = ['start'] + pos_list
    columns = pos_list + ['end']
    t_rows = ['start'] + pos_keys
    t_columns = pos_keys + ['end']

    # Initialize the table to zeros.
    table = numpy.zeros((len(rows), len(columns)))

    # Use list comprehension to get row and column indices.
    row_indices = [t_rows.index(row) for row in rows]
    column_indices = [t_columns.index(col) for col in columns]

    # Populate the new table using indices.
    for i, row_index in enumerate(row_indices):
        for j, column_index in enumerate(column_indices):
            table[i, j] = transition_table[row_index, column_index]

    return table

def observed_likelihoods(sentence, pos_list, sentence_dic, likelihood_table, l_rows, l_columns):
    # Define the rows and columns for the new table.
    rows = pos_list + ['end']
    columns = sentence + ['end']

    # Initialize the table with zeros.
    table = numpy.zeros((len(rows), len(columns)))

    # Set the bottom-right cell to 1.0.
    table[-1, -1] = 1.0

    # For each word in the sentence, get its likelihood.
    for i, word in enumerate(sentence):
        word_pos = sentence_dic[i]
        
        # Try to find the word's index in the likelihood table's rows.
        l_row_i = l_rows.index(word.lower()) if word.lower() in l_rows else -1

        # For each part-of-speech tag associated with the word, get its likelihood.
        for pos in word_pos:
            l_column_i = l_columns.index(pos)
            likelihood = likelihood_table[l_row_i][l_column_i] if l_row_i != -1 else 0.00001
            table[pos_list.index(pos), i] = likelihood

    return table

def viterbi_algo(observed, sentence, pos_list, transitions):    
    # Define rows and columns for the Viterbi table.
    rows = ['start'] + pos_list + ['end']
    columns = ['start'] + sentence + ['end']

    # Initialize the Viterbi and path tables.
    viterbi = numpy.zeros((len(rows), len(columns)))
    path = numpy.zeros((len(rows), len(columns)), dtype=int)

    # Set the initial value.
    viterbi[0, 0] = 1

    # List to store indices of rows with non-zero probabilities in the previous column.
    prev_rows = [0]

    # For each column in the Viterbi table, calculate probabilities.
    for j in range(1, len(columns)):
        curr_rows = []

        for i in range(1, len(rows)):
            like = observed[i-1][j-1]
            if like > 0:
                curr_rows.append(i)

                for k in prev_rows:
                    previous_vit = viterbi[k][j-1]
                    transition_prob = transitions[k][i-1]
                    calc = previous_vit * like * transition_prob

                    if calc > viterbi[i][j]:
                        viterbi[i][j] = calc
                        path[i][j] = k

        prev_rows = curr_rows

    # Backtrack to find the most likely sequence of POS tags.
    sentence_tag = []
    _row = len(rows) - 1

    for j in range(len(columns) - 1, 0, -1):
        value = int(path[_row][j])
        tag = (columns[j], rows[_row])
        sentence_tag.append(tag)
        _row = value

    # Reverse the list to get the tags in the correct order.
    sentence_tag.reverse()

    return sentence_tag
