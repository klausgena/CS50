#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int winner;
    int loser;
}
pair;
const int PAIRCOUNT = 10;
// pair pairs[PAIRCOUNT] = {{1,2},{1,4},{3,2}, {1,3},{3,4},{2,3}}; // final cycle
// pair pairs[PAIRCOUNT] = {{1,2},{2,3},{3,4},{4,3},{4,5},{5,1},{2,5},{1,6},{4,1}}; // badpairs
pair pairs[PAIRCOUNT] = {{1,2},{2,3},{3,4},{4,3},{4,5},{5,1},{2,5},{1,6},{4,1},{6,1}}; // badpairs final cycle 10
//pair pairs[PAIRCOUNT] = {{0,1},{1,2},{2,3},{3,2},{2,0}};
//pair pairs[PAIRCOUNT] = {{1,2},{2,3},{4,3},{5,4},{1,5},{6,1},{6,4}}; // goodpairs
bool cycle(int winner, int loser, int locked_count, int selected_pairs[], bool visited[]);

int main ()
{
    int locked_count = 0;
    int selected_pairs[PAIRCOUNT];
    selected_pairs[0] = 0;
    for (int i = 0; i < PAIRCOUNT ; i++)
    {
        bool visited[PAIRCOUNT]; // nieuw
        for (int j = 0; j < PAIRCOUNT; j++)
        {
                visited[j] = false;
        }
        if (!cycle(pairs[i].winner, pairs[i].loser, locked_count, selected_pairs, visited))
        {
           printf("Hoera! Paar %d, %d is goed!\n", pairs[i].winner, pairs[i].loser);
            selected_pairs[locked_count] = i;
            locked_count++;
        }
    }
    return 0;
}


// does loser win a locked pair?
// move along path
bool cycle(int winner, int loser, int count, int selected_pairs[], bool visited[])
{
    bool is_winner = false;
    int current_winner;
    int current_loser;
    int current_pair;
    for (int i = 0; i < count; i++)
    {
        current_winner = pairs[selected_pairs[i]].winner;
        current_loser = pairs[selected_pairs[i]].loser;
        current_pair = selected_pairs[i];
        // check if loser equals next winner: CREATES LINK
        // maybe make array with all links? Starting with first winner?
        if (loser == current_winner && visited[current_pair] == false) // nieuw
        {
            visited[current_pair] = true; // nieuw that should be number of pair
            if (winner == current_loser)
            // if those two are the same, we've detected a cycle.
            {
            return true;
            break;
            }
        }
    }
        else
            {
            // if not, we go looking for another link.
            return cycle(winner, loser, count, selected_pairs, visited);
            }
    }
    return false;
}