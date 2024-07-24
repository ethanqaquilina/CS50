// Implements a dictionary's functionality

#include <cs50.h>
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
// 26^2 will cover every letter and second letter
const unsigned int N = 676;

// Hash table
node *table[N];

// Number of words variable
int numOfwords = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word
    int hashIndex = hash(word);

    // Go through linked list
    node *ptr = table[hashIndex];

    while (ptr != NULL)
    {
        // Return true if word is found
        const char *curWord = ptr->word;
        if (strcasecmp(curWord, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    // Return false if not found
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Sorts Alphabetically by first and second letter
    if (strlen(word) > 1)
    {
        return ((toupper(word[0]) - 'A') * 10) + (toupper(word[1]) - 'A');
    }
    return (toupper(word[0]) - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *dFile = fopen(dictionary, "r");
    if (dFile == NULL)
    {
        printf("Error opening the Dictionary.\n");
        return false;
    }

    // Read each word in file to buffer
    char buffer[LENGTH + 1];
    while (fscanf(dFile, "%s", buffer) != EOF)
    {
        // Make node to store new word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Error making node.\n");
            return false;
        }

        // Copy new word into node
        strcpy(n->word, buffer);

        // Get the hash index
        int hIndex = hash(buffer);

        // Set the node to the front of the hashtable index
        n->next = table[hIndex];
        table[hIndex] = n;

        numOfwords++;
    }
    // Close the dictionary file
    fclose(dFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Returns number of words
    return numOfwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Go through each table array linked list and free each node
    for (int i = 0; i < N; i++)
    {
        node *rmptr = table[i];
        node *ptr = table[i];

        while (ptr != NULL)
        {
            rmptr = ptr;
            ptr = ptr->next;
            free(rmptr);
        }
    }
    return true;
}
