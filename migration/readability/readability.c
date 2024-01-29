#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int letter_count(string text);

int word_count(string text);

int sentence_count(string text);

int grade_count(int lcount, int wcount, int scount);

int main(void)
{
    //Getting user input
    string input = get_string("Text: ");
    
    int lcount = letter_count(input);
    
    int wcount = word_count(input);
    
    int scount = sentence_count(input);
    
    int gcount = grade_count(lcount, wcount, scount);
    
    // If the output is < 1, print “Before grade 1”.
    if (gcount < 1)
    {
        printf("Before Grade 1\n");
    }
    // If the output is 16 or higher, print “Grade 16+”. 
    else if (gcount >= 16)
    {
        printf("Grade 16+\n");
    }
    // Else, print "Grade x".
    else
    {
        printf("Grade %i\n", gcount);
    }
}   

int letter_count(string text)
{
    // Define a variable of type int called “letter_counter” with the starting value of 0. 
    int letter_counter = 0;
    
    // Use a for loop to iterate over the text one character at a time.
    for (int i = 0; i < strlen(text); i++)
    {
        // Define a variable of type char named "letter" with the starting value of text[i].  
        char letter = text[i];
        
        // Use the function isalpha(x) to see if the character in the string "text" is alphabetical. 
        if (isalpha(letter) > 0)
        {
            // If isalpha returns > 0, add one to the letter_count.
            letter_counter++;
        }
        // If isalpha returns 0, ignore it and move on to the next character. 
    }
    return letter_counter;
}

int word_count(string text)
{
    // Define a variable of type int called “word_counter” with the starting value of 0. 
    int word_counter = 0;
    
    // Use a for loop to iterate over each character one by one in the text. 
    for (int i = 0; i < strlen(text); i++)
    {
        // Define a variable of type char named “letter” with the string value of text[i].
        char letter = text[i];
        
        // Use the function isspace(x) to see if that character is a space.
        if (isspace(letter) > 0)
        {
            // If isspace returns > 0 add one to the word counter. 
            word_counter++;
        }
    }
    // Add one to the word counter.
    word_counter++;
    return word_counter;
}

int sentence_count(string text)
{
    // Define a variable of type int called “sentence_counter” with the starting value of 0.
    int sentence_counter = 0;
    
    // Use a for loop to iterate over each character in the text. 
    for (int i = 0; i < strlen(text); i++)
    {
        // Define a variable of type char named “letter” with the string value of text[i].
        char letter = text[i];
        
        // Use the decimal ASCII chart to determine if the character is a “.”, “!” or a “?”
        if ((letter == '.') || (letter == '!') || (letter == '?'))
        {
            // If the if statement returns > 0 add one to the sentence counter.
            sentence_counter++;
        }
    }
    return sentence_counter;
}

int grade_count(int letter_count, int word_count, int sentence_count)
{
    // Define a variable of type float called L to calculate average number of letters per 100 words. Cast int variables to floats
    float L = (float) letter_count / (float) word_count * 100;
    
    // Define a variable of type float called S to calculate average number of sentences per 100 words. Cast int variables to floats.
    float S = (float) sentence_count / (float) word_count * 100;
    
    // Define a variable of type float called “grade_counter” containing the result of The Coleman-Liau formula.
    float grade_counter = 0.0588 * L - 0.296 * S - 15.8;
    
    // Round the formula’s output to the nearest integer and return it.
    return round(grade_counter);
}
