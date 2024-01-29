#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage. User must submit at least 1 candidate
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates.
    // The number of candidates is 1 less than the amount of command-line arguments.
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    // Iterate over each submitted candidate-name, and assign them the right position in the array.
    // Give each submitted candidate 0 votes to begin with.
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }
    // Prompt the user for an integer, representing the number of voters.
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Do the for loop as many times as there are candidates
    for (int i = 0; i < candidate_count; i++)
    {
        candidate *single = &candidates[i];

        // Compare the user's vote with each candidate's name
        if (strcmp(single->name, name) == 0)
        {
            // If the user's vote matches this candidate's names, increase that candidate's vote score.
            single->votes += 1;
            return true;
        }
    }
    // If none of the candidate's names match, return false.
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Sort the array of candidates by votes using selection sort
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int max_idx = i;

        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes > candidates[max_idx].votes)
            {
                max_idx = j;
            }
        }
        candidate temp = candidates[i];
        candidates[i] = candidates[max_idx];
        candidates[max_idx] = temp;
    }

    int highest_votes = candidates[0].votes;

    // Print the winner/winners with the highest votes
    for (int k = 0; k < candidate_count; k++)
    {
        if (highest_votes == candidates[k].votes)
        {
            printf("%s\n", candidates[k].name);
        }
        else if (candidates[k].votes < highest_votes)
        {
            break;
        }
    }
}

