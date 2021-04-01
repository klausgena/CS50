# include <stdio.h>
# include <cs50.h>

// Prototype
void meow(int times);
int get_positive_int(void);

int main(void)
{
    int i = get_positive_int();
    meow(i);
}

void meow(int times)
{
     for (int i = 0; i < times; i++)
     {
              printf("meow\n");
     }
}

int get_positive_int(void)
{
    int i = get_int("How many times? ");
    if (i > 0)
    {
        return i;
    }
    else
    {
       printf("This is not a positive int! ");
       return get_positive_int(); // dat heb ik hier goed gedaan! Met behulp van recursie.
    }
}