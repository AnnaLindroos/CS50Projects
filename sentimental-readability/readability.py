# TODO
import cs50
import ctypes
import math

# Getting user input
input = cs50.get_string("Text: ")

# Count number of letters
letter_counter = 0
word_counter = 0
sentence_counter = 0

for i in range(len(input)):

    character = input[i]

    if str.isalpha(character) == True:
        letter_counter = letter_counter + 1
    elif str.isspace(character) == True:
        word_counter = word_counter + 1
    elif ord(character) == 46 or ord(character) == 33 or ord(character) == 63:
        sentence_counter = sentence_counter + 1

# Add one to the word counter
word_counter = word_counter + 1

# Calculate average number of letters per 100 words
letters_average = (float(letter_counter) / float(word_counter)) * 100

# Calculate average number of sentences per 100 words
sentences_average = (float(sentence_counter) / float(word_counter)) * 100

# Calculate grade based on formula
grade_counter = (0.0588 * letters_average) - (0.296 * sentences_average) - 15.8

# Round float to nearest int and then print grade
round(grade_counter)
if grade_counter < 1:
    print("Before Grade 1")
elif grade_counter >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(grade_counter)}")