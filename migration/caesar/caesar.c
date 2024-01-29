#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

bool are_arguments_valid(int argcount, string argvalues[]);

string ciphertext(string plaintext, int key);

int main(int argc, string argv[])
{
    // If user didn't supply 2 arguments, exit with code 1
    if (are_arguments_valid(argc, argv) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]) % 26;

    string plaintext = get_string("plaintext:");

    string result = ciphertext(plaintext, key);

    printf("ciphertext: %s\n", result);

    return 0;
}

bool are_arguments_valid(int argcount, string argvalues[])
{
    // The user must supply 2 arguments
    if (argcount != 2)
    {
        return false;
    }

    string submitted_key = argvalues[1];

    // The user must supply one integer for the key
    // Every character in the string must be a number
    for (int i = 0, n = strlen(submitted_key); i < n; i++)
    {
        if (isdigit(submitted_key[i]) == 0)
        {
            return false;
        }
    }

    return true;
}

string ciphertext(string plaintext, int key)
{
    // Allocate enough space to store our result string
    string transform = malloc(strlen(plaintext));

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char letter = plaintext[i];

        // Non-alphabetical characters should not be ciphered
        if (isalpha(letter) == 0)
        {
            transform[i] = letter;

            continue;
        }

        // Cipher the letter
        int addingkey = letter + key;

        // Wrap around the alphabet if the letter is outside of the ASCII range
        // Casing of the plaintext letter must be preserved
        if (isupper(letter) > 0 && addingkey > 90)
        {
            addingkey -= 26;
        }
        else if (islower(letter) > 0 && addingkey > 122)
        {
            addingkey -= 26;
        }

        transform[i] = addingkey;
    }
    return transform;
}