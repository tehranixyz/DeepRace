import re
import itertools
import os
cwd = os.getcwd()
from collections import Counter
import numpy as np
import pickle

"""
Prepare Data
"""
# directory to save the training data
save_dest = cwd + "/saved_data/"

# directory to load the AST files
ast_folder = cwd + "/AST/"

# directory to load the source code files
source_codes_folder = cwd + "/source_codes/"

# directory to save the output html file
output_html = cwd + "/output_html/"

# this variable is used for calculating average length of token vectores
trainset_average_length = 0

# keeping track of names of files
file_names = []

# keeping the all tokens vectors in one variable
untouched_token_vectors = []


def clean_str(string):
    """
    Tokenization/string cleaning for datasets.
    Original taken from https://github.com/yoonkim/CNN_sentence/blob/master/process_data.py
    """
    return string.strip().lower()


def load_data_and_labels():
    """
    Loads polarity data from files, splits the data into tokens and generates labels.
    Returns split vectos and labels.
    """
    # Load data from files
    positive_examples = []
    for file in os.listdir('with_datarace'):
        filename = os.fsdecode(file)
        ast_file = open('with_datarace\\' + filename, 'r')
        token_vector = ast_file.read()
        positive_examples.append(token_vector)
        file_names.append(filename)

    negative_examples = []
    for file in os.listdir('without_datarace\\'):
        filename = os.fsdecode(file)
        ast_file = open('without_datarace\\' + filename, 'r')
        token_vector = ast_file.read()
        negative_examples.append(token_vector)  # List of lists
        file_names.append(filename)

    positive_examples = [s.strip() for s in positive_examples]
    negative_examples = [s.strip() for s in negative_examples]

    # Split by words
    x_text = positive_examples + negative_examples  # why we didn't cobine it from the beginning?
    x_text = [clean_str(sent) for sent in x_text]
    x_text = [s.split(" ") for s in x_text]

    # Generate labels
    positive_labels = [[0, 1] for _ in positive_examples]
    negative_labels = [[1, 0] for _ in negative_examples]
    y = np.concatenate([positive_labels, negative_labels], 0)

    return [x_text, y]


def pad_sentences(sentences, padding_word="PAD"):
    """
    Pads all token vectors to the same length. The length is defined by the longest token vector.
    Returns padded token vectors.
    """
    sequence_length = max(len(x) for x in sentences)
    print('vector size: ' + str(sequence_length))
    global trainset_average_length
    trainset_average_length = sequence_length
    padded_sentences = []
    for i in range(len(sentences)):
        sentence = sentences[i]
        num_padding = sequence_length - len(sentence)
        new_sentence = sentence + [padding_word] * num_padding
        padded_sentences.append(new_sentence)
    return padded_sentences


def average_length(sentences, padding_word="PAD"):
    """
    Pads all token vectors to the same length. The length is defined by calculating the avg length of all token vectors.
    Returns padded token vectors.
    """
    global trainset_average_length
    number_of_all = 0
    sum = 0
    averaged_sentences = []
    for i in range(len(sentences)):
        sentence = sentences[i]
        sum = sum + len(sentence)
        number_of_all = number_of_all + 1
    average = int(sum / number_of_all)
    average = 35572
    trainset_average_length = average
    for i in range(len(sentences)):
        sentence = sentences[i]
        if len(sentence) < average:
            num_padding = average - len(sentence)
            new_sentence = sentence + [padding_word] * num_padding
            averaged_sentences.append(new_sentence)
        elif len(sentence) > average:
            new_sentence = sentence[:average]
            averaged_sentences.append(new_sentence)
        else:
            averaged_sentences.append(sentence)
    print('Average Length is: ' + str(average))
    return averaged_sentences


def build_vocab(sentences):
    """
    Builds a vocabulary mapping from token to index based on the vector.
    Returns vocabulary mapping and inverse vocabulary mapping.
    """
    # Build vocabulary
    word_counts = Counter(itertools.chain(*sentences))
    # Mapping from index to word
    vocabulary_inv = [x[0] for x in word_counts.most_common()]
    vocabulary_inv = list(sorted(vocabulary_inv))
    # Mapping from word to index
    vocabulary = {x: i for i, x in enumerate(vocabulary_inv)}
    return [vocabulary, vocabulary_inv]


def build_input_data(sentences, labels, vocabulary):
    """
    Maps token vectors and labels to vectors based on a vocabulary.
    """
    # x = np.array([[vocabulary[word] for word in sentence] for sentence in sentences])

    # Uncomment this if we have unprecedented tokens
    for sentence_i in range(len(sentences)):
        for word_j in range(len(sentences[sentence_i])):
            if sentences[sentence_i][word_j] in vocabulary:
                sentences[sentence_i][word_j] = vocabulary[sentences[sentence_i][word_j]]
            else:
                sentences[sentence_i][word_j] = 1
    x = np.array(sentences)
    y = np.array(labels)
    return [x, y]


# saving the processed data into files
def save_data(sentences_padded, file_names, vocabulary, vocabulary_inv, mapped_token_vectores, labes):
    with open(save_dest + "senteces_padded.pkl", 'wb') as f:
        pickle.dump(sentences_padded, f, pickle.HIGHEST_PROTOCOL)
        f.close()

    with open(save_dest + "file_names.pkl", 'wb') as f:
        pickle.dump(file_names, f, pickle.HIGHEST_PROTOCOL)
        f.close()

    with open(save_dest + "vocabulary.pkl", 'wb') as f:
        pickle.dump(vocabulary, f, pickle.HIGHEST_PROTOCOL)
        f.close()

    with open(save_dest + "vocabulary_inv.pkl", 'wb') as f:
        pickle.dump(vocabulary_inv, f, pickle.HIGHEST_PROTOCOL)
        f.close()

    with open(save_dest + "mapped_token_vectores.pkl", 'wb') as f:
        pickle.dump(mapped_token_vectores, f, pickle.HIGHEST_PROTOCOL)
        f.close()

    with open(save_dest + "labels.pkl", 'wb') as f:
        pickle.dump(labes, f, pickle.HIGHEST_PROTOCOL)
        f.close()

    with open(save_dest + "token_vector_length.pkl", 'wb') as f:
        pickle.dump(len(sentences_padded[0]), f, pickle.HIGHEST_PROTOCOL)
        f.close()


# loading previously processed data from disk
def load_prev_saved_data():
    with open(save_dest + 'mapped_token_vectores.pkl', 'rb') as f:
        x = pickle.load(f)
        f.close()

    with open(save_dest + 'labels.pkl', 'rb') as f:
        y = pickle.load(f)
        f.close()

    with open(save_dest + 'vocabulary.pkl', 'rb') as f:
        vocabulary = pickle.load(f)
        f.close()

    with open(save_dest + 'vocabulary_inv.pkl', 'rb') as f:
        vocabulary_inv = pickle.load(f)
        f.close()

    return [x, y, vocabulary, vocabulary_inv]


def load_test_data():
    sentences, labels = load_data_and_labels()
    sentences_padded = average_length(sentences)

    with open(save_dest + 'vocabulary.pkl', 'rb') as f:
        vocabulary = pickle.load(f)
        f.close()

    with open(save_dest + 'vocabulary_inv.pkl', 'rb') as f:
        vocabulary_inv = pickle.load(f)
        f.close()

    x, y = build_input_data(sentences_padded, labels, vocabulary)

    return [x, y, vocabulary, vocabulary_inv]


def load_data(avg_len=False, load_saved_data=False, load_testdata=False):
    """
    Loads and preprocessed data for the dataset.
    Returns input vectors, labels, vocabulary, and inverse vocabulary.
    """

    if load_testdata:
        x, y, vocabulary, vocabulary_inv = load_test_data()

    elif load_saved_data:
        print("Loading data from previously saved data")
        x, y, vocabulary, vocabulary_inv = load_prev_saved_data()
    else:
        print("Loading and prosseing token vectors")
        # Load and preprocess data
        sentences, labels = load_data_and_labels()
        if avg_len:
            sentences_padded = average_length(sentences)
            print("Padding all vectors to avg length")
        else:
            sentences_padded = pad_sentences(sentences)
            print("Padding all vectors to the longest length")

        vocabulary, vocabulary_inv = build_vocab(sentences_padded)
        x, y = build_input_data(sentences_padded, labels, vocabulary)

        save_data(sentences_padded, file_names, vocabulary, vocabulary_inv, x, y)

    # buggy_testset = build_test_data_buggy(vocabulary)
    # safe_testset = build_test_data_safe(vocabulary)
    return [x, y, vocabulary, vocabulary_inv]


def read_ast(file_name):
    ast = [line.rstrip('\n') for line in open(ast_folder + file_name)]
    return ast


def read_source_code_file(file_name):
    source_code = [line.rstrip('\n') for line in open(source_codes_folder + file_name)]
    return source_code


# creates a dictionary contain the line of code as key and the impact probability as value

# Method => 'maximum', 'average', 'only_parent'
# maximum => impact probability is the maximum among the parent and children nodes
# average => impact probability is the average of the parent and children nodes
# only_parent => discard the children nodes, only takes into account the impact probability of the parent node
def create_source_lines_values(ast_as_list, ast_intrst_lines, method="only_parent"):
    lines_probability = {}

    # discards tokens related to children nodes
    if method == "only_parent":
        for ast_line_number, impact_probab in ast_intrst_lines.items():
            # we discard padding tokens
            if ast_line_number < len(ast_as_list):
                print(ast_as_list[ast_line_number])
                match = re.search(r'<line:(\S+):', ast_as_list[ast_line_number])
                if match:
                    lines_probability[match.group(1)] = impact_probab

    # considers children nodes
    else:
        for ast_line_number, impact_probab in ast_intrst_lines.items():
            if ast_line_number < len(ast_as_list):
                print(ast_line_number)
                match = re.search(r'<line:(\S+):', ast_as_list[ast_line_number])
                if match:
                    print("found the source code line number")
                    source_code_line = match.group(1)
                    print("source code line is " + str(source_code_line))
                    lines_probability[source_code_line] = []
                    lines_probability[source_code_line].append(impact_probab)
                else:
                    print("line number not found")
                    current_line = ast_line_number
                    while match is None:
                        current_line -= 1
                        if current_line < 0:
                            break
                        print("going to line " + str(current_line) + " in AST")
                        match = re.search(r'<line:(\S+):', ast_as_list[current_line])
                    if current_line < 0:
                        continue
                    source_code_line = match.group(1)
                    print("found the source code line number")
                    print("source code line is " + str(source_code_line))
                    if source_code_line not in lines_probability:
                        lines_probability[source_code_line] = []
                        lines_probability[source_code_line].append(impact_probab)
                    else:
                        lines_probability[source_code_line].append(impact_probab)

        # taking the maximum value in the children
        if method == "maximum":
            for line, value in lines_probability.items():
                if len(value) > 1:
                    lines_probability[line] = max(value)
                else:
                    lines_probability[line] = value[0]
        # caculating the average value in children
        else:
            for line, value in lines_probability.items():
                if len(value) > 1:
                    lines_probability[line] = sum(value) / len(value)
                else:
                    lines_probability[line] = value[0]

    return lines_probability


# highliting the source code and saving it as a HTML file
def highlight_source_code(filename, source_code_intrst_lines, method):
    source_code_list = read_source_code_file(filename[:-4])
    for i in range(len(source_code_list)):
        source_code_list[i] = source_code_list[i].replace('<', '&lt;');
        source_code_list[i] = source_code_list[i].replace('>', '&#62;');
    for line_number, probab in source_code_intrst_lines.items():
        print(line_number, probab)
        actual_line_num = int(line_number) - 1
        if actual_line_num < len(source_code_list):
            actual_content = source_code_list[actual_line_num]
            source_code_list[actual_line_num] = "<span style=\"background-color: rgba(255, 0, 0, " + str(
                probab) + ");\">" + actual_content + "</span>"
            print(source_code_list[actual_line_num])

    with open(output_html + filename + '_' + method + '.html', 'w') as f:
        f.write("<pre>");
        for item in source_code_list:
            f.write(item + "\n");
        f.write("</pre>");