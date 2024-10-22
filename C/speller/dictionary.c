// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashNum = hash(word);
    node *cursor = table[hashNum];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
            return true;
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dctFile = fopen(dictionary, "r");

    if (dctFile == NULL)
        return false;

    char str[LENGTH + 1];

    while (fscanf(dctFile, "%s", str) != EOF)
    {
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
            return false;
        strcpy(tmp->word, str);
        int hashNum = hash(str);

        if (table[hashNum] == NULL)
            tmp->next = NULL;
        else
            tmp->next = table[hashNum];
        table[hashNum] = tmp;
        count++;
    }
    fclose(dctFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false

void freenode(node *n)
{
    if (n->next != NULL)
        free(n->next);
    free(n);
}

bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
            freenode(table[i]);
    }
    return true;
}
