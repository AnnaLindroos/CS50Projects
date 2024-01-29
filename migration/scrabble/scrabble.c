#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int player1score = compute_score(word1);
    int player2score = compute_score(word2);

    // TODO: Print the winner

    if (player1score < player2score)
    {
        printf("Player 2 wins!\n");
    }
    else if (player2score < player1score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1score == player2score)
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    
    // Iterate over each letter in the word and add each letter's point
    
    for (int counter = 0; counter < strlen(word); counter++)
    {
        char letter = word[counter];
        int casted = (int) letter;
        
        if (isalpha(letter) == 0)
        {
            continue;
        }
        
        if (isupper(letter) > 0)
        {
            casted += 32;
        }
        
        casted -= 97;
        score += POINTS[casted];
    }
    return score;
}
