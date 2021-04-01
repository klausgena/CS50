# include <cs50.h>
# include <stdio.h>

int main (void)
{
    char c = get_char("Do you agree? ");
    if (c == 'y' || c == 'Y') // chars moeten enkel qutoed zijn
    {
        printf("Agreed.\n");
    }
    if (c == 'n' || c == 'N')
    {
        printf("Not agreed.\n");
    }
}