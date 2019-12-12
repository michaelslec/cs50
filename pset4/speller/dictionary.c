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
node *root = NULL;

size_t dictionary_size = 0;

int has_children(node *ptr)
{
    for (size_t i = 0; i < N; ++i)
    {
        if (ptr->children[i])
            return i;
    }

    return -1;
}

char tochar(int index)
{
    if (index == N - 1)
    {
        return '\'';
    }

    return index + 'a';
}

unsigned int toindex(char c)
{
    if (c == '\'')
    {
        return N - 1;
    }

    return tolower(c) - 'a';
}

node* create_trie()
{
    node *temp = malloc(sizeof(node));
    if (temp == NULL)
    {
        fprintf(stderr, "Could not allocate memory for trie\n");
        return false;
    }

    temp->is_word = false;

    for (int i = 0; i < N; i++)
    {
        temp->children[i] = NULL;
    }

    return temp;
}

void free_trie(node *trav)
{
    for (size_t i = 0; i < N; i++)
    {
        if(trav->children[i] != NULL)
        {
            free_trie(trav->children[i]);
        }
    }

    free(trav);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Initialize trie
    root = create_trie();
    if (root == NULL)
    {
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // iterator through trie
        node *iter = root;

        // insert word into trie
        for (size_t i = 0, index = 0; i < strlen(word); ++i)
        {
            // returns index to insert current letter
            // EX: a = 0, c = 2, ' = 26
            index = toindex(word[i]);

            // If node does not exists
            if (iter->children[index] == NULL)
            {
                // assign NULL node to real node
                iter->children[index] = create_trie();
            }

            // traverse into new node
            iter = iter->children[index];
        }

        // finished for loop represents finished word
        iter->is_word = true;
        ++dictionary_size;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_size;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // pointer to traverse trie
    node *ptr = root;

    // for each character in word
    for (size_t i = 0, index = 0; i < strlen(word); ++i)
    {
        // get index of char
        index = toindex(word[i]);

        ptr = ptr->children[index];

        // if letter does not exist
        if (ptr == NULL)
        {
            return false;
        } 
    }

    return ptr->is_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    if(root != NULL)
    {
        node *trie = root;
        free_trie(trie);
        return true;
    }

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

    for (int i = 0; i < N; i++)
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
/*     load("dictionaries/custom"); */
/*     unload(); */
/*  */
/*     display(root, word, 0); */
/*  */
/*     return 0; */
/* } */
