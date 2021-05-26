from cs50 import get_string
import re

# Check the readability index of a certain text


def count_letters(s):
    # count letters in string. Spaces and punctuation
    # should be left out.
    count = 0
    for l in s:
        if l.isalnum():
            count = count + 1
    return count
    

def count_words(s):
    # count words in a sentence
    # splitting them by space
    a = s.split()
    return len(a)
    

def count_sentences(s):
    # count the sentences in a
    # text. Split by punctuation marks.
    a = re.split('[.?!]', s)
    return len(a) - 1
    

def calculate_index(l, w, s):
    # calculate the Coleman-Liau index
    # calculate average letters every 100 words
    average_L = (l/w) * 100
    # calculate average sentences every 100 words
    average_S = (s/w) * 100
    # apply formula
    index = (0.0588 * average_L) - (0.296 * average_S) - 15.8
    # return the index as an integer
    return round(index)
    

def main():
    # calculate the readability index of one or more
    # sentences
    text = get_string("Text: ")
    # do the countings
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    print(f'Your text has {letters} letters, {words} words and {sentences} sentences.')
    # calculate the index
    index = calculate_index(letters, words, sentences)
    # define the grades
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f'Grade {index}')


main()