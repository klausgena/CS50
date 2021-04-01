#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int winner;
    int loser;
}
pair;
pair pairs[5] = {{0,1},{1,2},{2,3},{3,2},{2,0}};
bool locked[5][5];

bool cycle(int winner, int loser, int step);
int main ()
{
    for (int i = 0; i < 5 ; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser, 5))
        {
            printf("Hoera: paar %d (%d, %d) is een goed paar.\n", i + 1, pairs[i].winner, pairs[i].loser);
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return 0;
}



bool cycle(int winner, int loser, int step)
{
  for (int i = 0; i < step; i++)
  {
      int w = pairs[i].winner;
      int l = pairs[i].loser;
      if (w == loser && l == winner && locked[loser][winner] == true)
      {
          printf("Fuck!\n");
          return true;
      }
  }
  return false;
}
