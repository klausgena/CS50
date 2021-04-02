#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int winner;
    int loser;
}
pair;
const int PAIRCOUNT = 11;
//pair pairs[PAIRCOUNT] = {{1,2},{1,4},{3,2}, {1,3},{3,4},{2,3}}; // final cycle 6
// pair pairs[PAIRCOUNT] = {{1,2},{2,3},{3,4},{4,3},{4,5},{5,1},{2,5},{1,6},{4,1}}; // badpairs
pair pairs[PAIRCOUNT] = {{1,2},{2,3},{3,4},{4,3},{4,5},{5,1},{2,5},{1,6},{4,1},{6,1},{3,1}}; // badpairs final cycle 11

//pair pairs[PAIRCOUNT] = {{0,1},{1,2},{2,3},{3,2},{2,0}};
//pair pairs[PAIRCOUNT] = {{1,2},{2,3},{4,3},{5,4},{1,5},{6,1},{6,4}}; // goodpairs 7
bool cycle(int winner, int loser, int locked_count, int selected_pairs[], bool visited[], bool flag, int original_loser);

int main ()
{
    int locked_count = 0;
    int selected_pairs[PAIRCOUNT];
    selected_pairs[0] = 0;
    for (int i = 0; i < PAIRCOUNT ; i++)
    {
        bool visited[PAIRCOUNT]; // nieuw
        bool flag = false;
        int original_loser = pairs[i].loser;
        for (int j = 0; j < PAIRCOUNT; j++)
        {
                visited[j] = false;
        }
        if (!cycle(pairs[i].winner, pairs[i].loser, locked_count, selected_pairs, visited, flag, original_loser))
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
bool cycle(int winner, int loser, int count, int selected_pairs[], bool visited[], bool flag, int original_loser)
{
    bool is_winner = false;
    int current_winner;
    int current_loser;
    int current_pair;
    if (count == 0)
   {
      return false;
       // first pair is always ok.
    }
    for (int i = 0; i < count; i++)
    {
        // This for loop checks if loser is a winner and is not visited.
        // It does NOTHING ELSE!
        current_winner = pairs[selected_pairs[i]].winner;
        current_loser = pairs[selected_pairs[i]].loser;
        current_pair = selected_pairs[i];
        // CREATES LINK
        // IDEA: maybe make array with all links? Starting with first winner?
        if (loser == current_winner && visited[current_pair] == false) // nieuw
        {
            visited[current_pair] = true; // nieuw that should be number of pair
            is_winner = true;
            break;
        }
    }
        if (is_winner == true && winner == current_loser)
        {
            return true;
            // if those two are the same, we've detected a cycle and exit.
        }
        else if (is_winner == true) // voorwaarde toegevoegd voor middencase
        {
                // here we should keep making those links with the follo
                // wing losers, maybe we find a cycle
            // but if it doesn't find what it looks for on a first run, a second one, or a third might be needed...
            //flag = true;
          cycle(winner, current_loser, count , selected_pairs, visited, flag, original_loser); // return verwijderd
        }
        // dit ook tijdelijk verwijderd
        // else if (flag == true)
        // {
        //     flag = false;
        //     // but if the loop found a winner, but didn't create a cycle, we should
        //     // check if there's a second or more winner we overlooked...
        //     return cycle(winner, original_loser, count, selected_pairs, visited, flag, original_loser); // TIJDELIJK UIT
        // }
        else if (is_winner == false)
        {
          // no options left
            return false;
        }
        else
        {
            return true;
        }
//return false; // is dat hier op zijn plaats?
return true;
}