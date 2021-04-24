// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 9973; // the hashing modulo has to be a large prime;

// Hash table
node *table[N];
// initialize word_count
int word_count = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // first check hash.
    int hash_value = hash(word);
    node *n = table[hash_value];
    // check if array el is empty = misspelled
    if (n == NULL)
    {
        return false;
    }
    do
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    while (n != NULL);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
    int i = 0;
    while(word[i] != '\0')
    {
        int n = word[i] - 0; // turn char into int
        int p = 31; // prime number for hash
        // upper to lower
        if (n < 91 && n > 64)
        {
            n = n + 32 - 'a' + 1;
        }
        else if (n > 96)
        {
            n = n - 'a' + 1;
        }
        // the actual hashing function
        // https://cp-algorithms.com/string/string-hashing.html.
        hash = n * p ^ i + hash;
        // increase counter
        i++;
    }
    hash = hash % N;
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Cannot open dictionary file.\n");
        return false;
    }
    // initalize hash table
    for (int i = 0; i < N ; i++)
    {
        node *list = NULL;
        table[i] = list;
    }
    // read file
    char c;
    while((c = getc(dict)) != EOF)
    {
        int i = 0;
        // create node with hash, word and null pointer
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        // read word
        while (c != '\n')
        {
            n->word[i] = c;
            c = getc(dict);
            i++;
        }
        // nog een \0 toevoegen
        n->word[i] = '\0';
        // calculate hash
        int hash_value = hash(n->word);
        // don't loose link
        n->next = table[hash_value];
        // insert in front of
        table[hash_value] = n;
        // count every word
        word_count++;
    }
    fclose(dict);
    return true; // veranderen naar true
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // visit every el in table
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        // go to last el in each linked list
        if (n == NULL)
        {
            continue;
        }
        if (n->next == NULL)
        {
            free(n);
            continue;
        }
        // free last el, go to the one before, free that one, etc.
        do
        {
           node *tmp = n;
           n = n->next;
           free(tmp);
        }
        while (n != NULL);
        // free(n); double free or corruption?
    }
    return true;
}
