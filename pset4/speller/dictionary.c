// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool         is_word;
    struct node *children[N];
} node;

// Represents a trie
node *root;

const int kAPOSTROPHE = -58;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // iterator through trie
        node *iter = root;
        // holds related array index for char. IE a=0, c=2, '=26
        int index = 0;

        for (size_t i = 0; i < strlen(word); ++i)
        {
            // a-z enum with a=0
            index = word[i] - 'a';

            // apostrophe = 39, 'a' = 97, 39 - 97 = -58
            if (index == kAPOSTROPHE) // -58
            {
                index = N - 1;
            }

            // If node does not exists
            if (!iter->children[index])
            {
                // temporary storage
                node *temp = malloc(sizeof(node));

                // check if memory was allocated
                if (!temp)
                {
                    fprintf(stderr, "could not allocate memory for trie\n");
                    return false;
                }

                // assign NULL node to real node
                iter->children[index] = temp;
            }

            // traverse into new node
            iter = iter->children[index];
        }

        // finished for loop represents finished word
        iter->is_word = true;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}

// Pulled from https://www.geeksforgeeks.org/trie-display-content/
void display(node *ptr, char str[], int level)
{
    // If node is leaf node, it indicates end
    // of string, so a null character is added
    // and string is displayed
    if (ptr->is_word)
    {
        str[level] = '\0';
        printf("%s\n", str);
    }

    int i;
    for (i = 0; i < N; i++)
    {
        // if NON NULL child is found
        // add parent key to str and
        // call the display function recursively
        // for child node
        if (ptr->children[i])
        {
            if (i == 26)
                str[level] = '\'';
            else
                str[level] = i + 'a';

            display(ptr->children[i], str, level + 1);
        }
    }
}

/* int main(void) */
/* { */
/*     char word[LENGTH]; */
/*     load("dictionaries/large"); */
/*  */
/*     display(root, word, 0); */
/*  */
/*     return 0; */
/* } */
