#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];

    // There needs to be 2 command line arguments
    if (argc != 2)
    {
        printf("Usage ./substitution key");
        return 1;
    }
    // Key must contain 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters");
        return 1;
    }

    for (int i = 0; i < strlen(key); i++)
    {
        for (int j = i + 1; j < strlen(key); j++)
        {
            // All characters must be alphabetical
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Key must contain 26 characters");
                return 1;
            }

            // No characters in the key are to be repeated
            else if (toupper(key[i]) == toupper(key[j]))
            {
                printf("Key must not repeat characters");
                return 1;
            }
        }
    }
    // Get plaintext from user
    string plaintext = get_string("plaintext: ");

    // Allocate memory for storing ciphertext
    string ciphertext = malloc(strlen(plaintext));

    // Create array for uppercase letters
    char uppercase[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    // Create array for lowercase letters
    char lowercase[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Output non-alphabetical characters unchanged
        if (isalpha(plaintext[i]) == 0)
        {
            plaintext[i] = ciphertext[i];
            continue;
        }
        // Convert plaintext letter to accurate key (uppercase)
        else if (isupper(plaintext[i]) != 0)
        {
            for (int alpha = 0; alpha < strlen(uppercase); alpha++)
            {
                if (plaintext[i] == uppercase[alpha])
                {
                    ciphertext[i] = toupper(key[alpha]);
                }
            }
        }
        // Convert plaintext letter to accurate key (lowercase)
        else
        {
            for (int beta = 0; beta < strlen(lowercase); beta++)
            {
                if (plaintext[i] == lowercase[beta])
                {
                    ciphertext[i] = tolower(key[beta]);
                }
            }
        }
    }

    // Print ciphertext
    printf("ciphertext: %s\n", ciphertext);
    free(ciphertext);
    return 0;
}