#include <stdio.h>
#include <cs50.h>

int prompt_number_in_range(int begin, int end); // prompt for number in certain range
void build_pyramid(int height);
void print_row(int length, int bricks);

int main(void)
{
    // prompt user for number between 1-8
    int i = prompt_number_in_range(1, 8);
    // else build pyramid
    build_pyramid(i);

}

int prompt_number_in_range(int begin, int end)
{
    int n = 0;
    do
    {
        n = get_int("Give us a number between %i and %i: ", begin, end);
    }
    while (n < begin || n > end); // moet hier or zijn en niet and, dommerik!
    return n;
}
void build_pyramid(int height)
{
    for (int i = 0; i < height ; i++)
    {
        print_row(height, i + 1);
        printf("\n");
    }
}
void print_row(int length, int bricks)
{

    for (int i = 0; i < length - bricks; i++)
    {
        printf(" ");
    }

    for (int i = 0; i < bricks ; i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < bricks ; i++)
    {
        printf("#");
    }
    //printf("\n");
}