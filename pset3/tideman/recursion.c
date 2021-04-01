#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int PAIRCOUNT = 9;

typedef struct
{
    int winner;
    int loser;
}
pair;
pair pairs[PAIRCOUNT] = {{1,2},{2,3},{3,4},{4,2},{4,5},{5,1},{2,5},{1,6},{4,1}}; // badpairs
// pair pairs[PAIRCOUNT] = {{1,2},{2,3},{4,3},{5,4},{1,5},{6,1},{6,4}}; // goodpairs
bool cycle(int winner, int loser, int locked_count, int selected_pairs[]);
int main ()
{
    int locked_count = 0;
    int selected_pairs[PAIRCOUNT];
    selected_pairs[0] = 0;
    for (int i = 0; i < PAIRCOUNT; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser, locked_count, selected_pairs))
        {
            printf("Hoera: paar %d (%d, %d) is een goed paar.\n", i + 1, pairs[i].winner, pairs[i].loser);
            locked_count++;
            selected_pairs[locked_count] = i;
        }
    }
    return 0;
}


// does loser win a locked pair?
// build path
bool cycle(int winner, int loser, int count, int selected_pairs[])
{
    int new_winner = pairs[count - 1].winner;
    int new_loser = pairs[count - 1].loser;
    if (count <= 0)
        return false;
    else if (loser == new_winner && winner == new_loser)
        return true;
    else
    {
        count--;
        return cycle(winner, loser, count, selected_pairs);
    }
}