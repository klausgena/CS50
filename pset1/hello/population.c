#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // vars
    int start_size = 0;
    int end_size = 0;
    int grow_size = 0;
    int years = 0;
    // Prompt for start size
    do
    {
        start_size = get_int("Start size: ");
    }
    while (start_size < 9);
    // Prompt for end size
    do
    {
        end_size = get_int("End size: ");
    }
    while (end_size < start_size);
    // Calculate number of years until we reach threshold
    grow_size = start_size;
    while (grow_size < end_size)
    {
        grow_size = grow_size + (grow_size / 3) - (grow_size / 4);
        years++;
    }
    // Print number of years
    printf("Years: %i\n", years);
}
