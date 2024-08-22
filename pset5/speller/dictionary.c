// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to obtain its hash value
    unsigned int hashValue = hash(word);
    // Search the hash table at the location specified by the word’s hash value
    node *cursor = table[hashValue];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // Return true if the word is found
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    // Return false if no word is found
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
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        return false;
    }

    // Read each word in the file
    char str[LENGTH + 1];
    while (fscanf(source, "%s", str) != EOF)
    {

        // Create space for a new hash table node
        //  Use malloc
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // Copy the word into the new node
        strcpy(n->word, str);

        // Hash the word to obtain its hash value
        unsigned int hashValue = hash(str);

        // Insert the new node into the hash table (using the index specified by its hash value)
        n->next = table[hashValue];
        table[hashValue] = n;

        word_count += 1;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freenode(table[i]);
        }
    }
    return true;
}
// Function to free nodes
void freenode(node *n)
{
    node *tmp;
    while (n != NULL)
    {
        tmp = n;
        n = n->next;
        free(tmp);
    }
}
