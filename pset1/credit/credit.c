# include <stdio.h>
# include <cs50.h>

// Checksum = vermenigvuldig elk tweede cijfer (onpaar), te beginnen met het voorlaatste) met 2. Tel die som bij elkaar op.
// Tel dat op met de som van de resterende cijfers. Het resultaat moet deelbaar zijn door 10 (eindigen op een 0, modulo 0).
// Het antwoord moet de naam retourneren of "invalid"
// get_long voor de user input (16 cijfers...)
// hoe kom je aan al die cijfers? Met een module %10 krijg je altijd het laatste cijfer!! geniaal.

long prompt_for_number(void);
string check_brand(long card);
bool checksum(long card);
// secondary helper functions
int calculate_length(long number);
int get_first_digits(long number);

int main(void)
{
    long card = prompt_for_number();
    string brand = check_brand(card); // als dat niet goed is, dan meteen invalid printen.
    bool valid = checksum(card);
    if (valid == 0)
    {
        printf("%s\n", brand);
    }
    else
    {
        printf("INVALID\n");
    }
}

long prompt_for_number(void)
{
    long number = get_long("What's your credit card number? ");
    return number;
}
string check_brand(long card)
{
    // check the length of the number and if it starts with the right nummbers.
    // Return brand or invalid.
    // AMEX = 34 of 37 (if 1e twee is ...) en is 15 cijfers lang
    // VISA = 4, lengte 13 OF 16
    // Master = 16 cijfers lang, begint met 51 .. 55
    int length = calculate_length(card);
    int first_digits = get_first_digits(card);
    string brand = "";

    if (length < 13 || length > 16)
    {
        brand = "INVALID";
    }
    else if ((length == 13 || length == 16) && (first_digits / 10) == 4)
    {
        brand = "VISA";
    }
    else if (length == 15 && (first_digits == 34 || first_digits == 37))
    {
        brand = "AMEX";
    }
    else if (length == 16)
    {
        for (int i = 51 ; i < 56 ; i++)
        {
            if (first_digits == i)
            {
                brand = "MASTERCARD";
                break;
            }
            else if (first_digits != i)
            {
                brand = "INVALID";
            }
        }
    }
    else
    {
        brand = "INVALID";
    }
    return brand;
}

bool checksum(long card)
{
    // take every second number starting from the first before last and multiply
    // it by 2, then sum them together. The rest of the numbers: sum. Sum the
    // 2 sums. The modulo %10 of the total should be 0.
    bool valid = 1;
    int length = calculate_length(card);
    int sum_1 = 0;
    int sum_2 = 0;
    int total = 0;
    long new_number = card;
    int number = 0;
    // code
    for (int i = 0; i < length ; i++)
    {
        if (i % 2 != 1)
        {
            number = new_number % 10;
            new_number = new_number / 10;
            sum_1 = sum_1 + number;
        }
        else
        {
            number = new_number % 10;
            new_number = new_number / 10;
            number = number * 2;
            if (number > 9)
            {
                int a = number / 10;
                int b = number % 10;
                number = a + b;
            }
            sum_2 = sum_2 + number;
        }
    }
    total = sum_1 + sum_2;
    if (total % 10 == 0)
    {
        valid = 0;
    }
    else
    {
        valid = 1;
    }

    return valid;
}

int calculate_length(long number)
{
    // calculate the length of a number
    int length = 0;
    long modulo = 10;
    long new_number = 0;
    // if number stops changing after ever increasing modulo,
    // we have found it's length.
    while (number != new_number)
    {
        new_number = number % modulo;
        length++;
        modulo = modulo * 10;
    }
    return length;
}

int get_first_digits(long number)
{
    // return the first two digits of a nummber
    int length = calculate_length(number);
    long divider = 1;
    for (int i = 0; i < length - 2; i++)
    {
        divider = divider * 10;
    }
    int first_digits = number / divider ;
    return first_digits;
}

// test nummer : 378282246310005
// test van cs50: 4003600000000014