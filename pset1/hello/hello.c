# include <stdio.h>
#include <cs50.h>

int main(void)
{
    // say user's name after input.
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}