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
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

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

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO check if name exists
    for (int i = 0; i < candidate_count; i++)
    {

        // if exists, add vote
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    // else return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest = 0;
    string winners[candidate_count];
    // TODO print candidate with the most votes.
    // get the name of the candidate with the most votes.
    // add the name to the array winners[].
    // possibly the highest number is not alone.
    // if there are TIES, print everybody with the highest score.
    // print the winner(s).
    for (int i = 0; i < candidate_count; i++)
    {
        // get highest vote
        int vote = candidates[i].votes;
        if (vote > highest)
        {
            highest = vote;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // get names with highest vote
        int vote = candidates[i].votes;
        string winner = candidates[i].name;
        if (vote == highest)
        {
            winners[i] = winner;
        }
        else
        {
            winners[i] = "";
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // if array el not empty, print name
        if (strcmp(winners[i], "") != 0) // hier zit ik met een probleem
        {
            printf("%s\n", winners[i]);
        }
    }
    return;
}

