#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get numbers from user
    int x = get_int("x: "); // die ints veroorzaken bug
    int y = get_int("y: ");
    float z = (float) x / (float) y; // en ik moet die dus omzetten in float. Dat et casten.
    printf("%f\n", z);
}