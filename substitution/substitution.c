#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string cipher(string key, string input);
bool check_key(string key);

int main(int argc, string argv[])
{
    // if no input: Usage: ./substitution key
    if (argc < 2)
    {
        printf("Usage: ./substitution key\n");
        //return 1;
        exit(1);
    }
    string cipherstring = "";
    string key = argv[1];
    // check if key is right
    bool check = check_key(key);
    if (check == 1)
    {
        exit(1);
    }
    else
    {
        string input = get_string("plaintext: ");
        cipherstring = cipher(key, input);
        printf("ciphertext: %s\n", cipherstring);
    }
    return 0;
}

string cipher(string key, string input)
{
    // create string with length of input
    string cipherstring = input;
    // transform input string into cipherstring.
    // change each char of input into equivalent char of key
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        char c = input[i];
        int v = 0;
        char k = 'a';
        if (isalpha(c))
        {
            // other ASCII pos if lower or upper
            // get the equivalent character
            // insert it into the cipherstring
            if (isupper(c))
            {
                v = (int) c - 65;
                k = toupper(key[v]);
                cipherstring[i] = k;
            }
            else
            {
                v = (int) c - 97;
                k = key[v];
                k = tolower(k);
                cipherstring[i] = k;
            }

        }
        else
        {
            cipherstring[i] = input[i];
        }
    }
    return cipherstring;
}

bool check_key(string key)
{
    int l = strlen(key);

    // not twice the same letter
    for (int i = 0; i < l; i++)
    {
        // check every char in key against key and count. If > 1: exit.
        int count = 0;
        for (int k = 0; k < l; k++)
        {
            if (key[i] == key[k])
            {
                count++;
            }
        }
        if (count > 1)
        {
            printf("Key must not contain doubles.\n");
            exit(1);
        }
    }
    for (int i = 0; i < l; i++)
    {

        // Key should contain only alphabetical signs
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            exit(1);
        }
    }
    // Key should be 26 characters long
    if (l > 26 || l < 26)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }
    return 0;
}