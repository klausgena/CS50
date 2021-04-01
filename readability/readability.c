# include <stdio.h>
# include <cs50.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
int calculate_index(int l, int w, int s);

int main(void)
{
    // calculate the readability index of one or more sentences.
    int grade = 0;
    string text = get_string("Text: ");
    int letters = 0;
    int words = 0;
    int sentences = 0;
    int index = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        letters = count_letters(text);
        words = count_words(text);
        sentences = count_sentences(text);
    }
    index = calculate_index(letters, words, sentences);
    if (index > 16)
    {
        printf("Grade 16+");
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", index);
    }
    printf("\n");
}

int count_letters(string s)
{
    // count letters in string. spaces and punctuation should be left out.
    int count = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalnum(s[i]))
        {
            count++;
        }
    }
    return count;
}

int count_words(string s)
{
    // count words in a sentence.
    int count = 1;
    bool flag = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isspace(s[i]) && flag == 0)
        {
            count++;
            flag = 1;
        }
        else
        {
            flag = 0;
        }
    }
    return count;
}

int count_sentences(string s)
{
    // count number of sentences in string
    int count = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char c = s[i];
        if (c == '.' || c == '?' || c == '!')
        {
            count++;
        }
    }
    return count;
}

int calculate_index(int l, int w, int s)
{
    // Calculate Coleman-Liau index
    float index = 0.0;
    int grade = 0;
    // gemiddeld aantal letters per 100 woorden
    float average_L = ((float) l / (float) w) * 100.0;
    // gemiddeld aantal zinnen per 100 woorden
    float average_S = ((float) s / (float) w) * 100.0;
    // formula: index = 0.0588 * L - 0.296 * S - 15.8
    index = (0.0588 * average_L) - (0.296 * average_S) - 15.8;
    grade = round(index);
    return grade;
}