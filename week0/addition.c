#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long x = get_long("X: "); // int is niet groot genoeg
    long y = get_long("y: ");

    printf("sum x and y = %li\n", x + y);
}