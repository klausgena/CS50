#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
// helper function
bool cycle(int winner, int loser, int count, int selected_pairs[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

             if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // check if name exists
        if (strcmp(name, candidates[i]) == 0)
        {
            // add rank to name and return true
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // process one voter's votes
    for (int i = 0; i < candidate_count - 1; i ++)
    {
        // give winner a point for every loser
        for (int j = i + 1; j < candidate_count - i + 1 && j < candidate_count; j++) // to prevent segmentation fault when only 2 candidates...
        {
            preferences[ranks[i]][ranks[j]]++;
            printf("prefs: %i", preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // check for each pair if it is a tie (if not 0)
    // you should check j i also!!!
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // important to match candidates' scores against each other
            int score = preferences[i][j] - preferences[j][i];
            if (score > 0)
           {
               pairs[count].winner = i;
               pairs[count].loser = j;
               count++;
           }
        }
    }
    // update global variable pair_count
    pair_count = count;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // for each pair in pairs
    // define difference
    // sort by difference
    // no sorting needed if 1 or less
    if (pair_count <= 1)
    {
        return;
    }
    int differences[pair_count]; // number of the pair + difference of this pair
    for (int i = 0; i < pair_count; i++)
    {
        int x = pairs[i].winner;
        int y = pairs[i].loser;
        int difference = preferences[x][y] - preferences[y][x];
        differences[i] = difference;
        printf("Difference: %i\n", difference);
    }
    // sort differences
    int swapped = 0;
    do
    {
        swapped = 0;
        for (int i = 0, j = 1; i < pair_count && j < pair_count ; i++, j++)
            {
                if (differences[i] < differences[j])
                    {
                        // use temp vars to reorder array
                        // also change order of difference to avoid infinite loop!
                        int small_diff = differences[i];
                        int big_diff = differences[j];
                        differences[i] = big_diff;
                        differences[j] = small_diff;
                        pair small = pairs[i];
                        pair big = pairs[j];
                        pairs[i] = big;
                        pairs[j] = small;
                        swapped++;
                    }
            }
    }
    while (swapped != 0);
    // return sorted pairs array
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // from the sorted pairs array, select the pairs to be locked
    // and make them true in the locked array. If cycle, skip!
    // first pair can be looked:
    int locked_count = 0;
    int selected_pairs[pair_count];
    selected_pairs[0] = 0;
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser, locked_count, selected_pairs))
        {
            printf("Hoera: paar %d (%d, %d) is een goed paar.\n", i + 1, pairs[i].winner, pairs[i].loser);
            locked[pairs[i].winner][pairs[i].loser] = true;
            selected_pairs[locked_count] = i;
            locked_count++;
        }
    }
   return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}
// helper function locked_pairs
bool cycle(int winner, int loser, int count, int selected_pairs[])
{
    bool is_winner = false;
    int current_winner;
    int current_loser;
    bool visited[count];
    int rest = 0;
    for (int i = 0; i < count; i++)

    // initialize visited with falses
    for (int i = 0; i < count ; i++)
    {
        visited[i] = false;
    }
    {
        current_winner = pairs[selected_pairs[i]].winner;
        current_loser = pairs[selected_pairs[i]].loser;

        if (loser == current_winner && visited[i] == false)
        {
            rest = count - i - 1;
            visited[i] = true;
            is_winner = true;
            break;
        }
        else
            rest = count - i - 1;
    }
    if (is_winner == true)
    {
        if (winner == current_loser)
            return true;
        else
            return cycle(winner, current_loser, count, selected_pairs);
    }
    else
    {
        if (rest <= 0)
            return false;
        else
            return cycle(winner, loser, rest, selected_pairs);
    }
}