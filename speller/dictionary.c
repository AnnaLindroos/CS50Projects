// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Word count
int words = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N] = { NULL };

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Hash word to obtain a hash value
    int index = hash(word);

    // Access linked list at that index in the hash table. Set trav to equal first element in linked list
    node *trav = table[index];

    // Traverse linked list, looking for the word.
    while (trav != NULL)
    {
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    // if trav == NULL, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;

    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';

    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dick = fopen(dictionary, "r");
    if (dick == NULL)
    {
        printf("Could not open file");
        return false;
    }

    char word[LENGTH + 1];

    // Read strings from file one at a time
    while (fscanf(dick, "%s", word) != EOF)
    {
        // Create a node for each new word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Not enough memory");
            return false;
        }

        // Copy word from dick into node's word field
        strcpy(n->word, word);

        // Hash word to obtain a hash value
        int idx = hash(word);

        // If this is the first node in the array at the current index,
        // set the next field to NULL to ensure end of list
        if (table[idx] == NULL)
        {
            n->next = NULL;
        }
        // Otherwise, set the next field to be equal to first node's next field
        else
        {
            n->next = table[idx]-> next;
        }

        // Insert node into hash table at that location
        table[idx] = n;

        // Add word to word count
        words++;

    }
    fclose(dick);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over all the buckets in the hash table
    for (int i = 0; i < N; i++)
    {
        // make current point to table's index first node
        node *current = table[i];
        node *cursor = table[i];

        while (current != NULL)
        {
            // Make cursor point to whatever is at current's next field
            cursor = cursor->next;
            free(current);
            current = cursor;
        }
    }
    return true;
}
