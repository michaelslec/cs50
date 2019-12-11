// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45
typedef struct node node;
node *              root;

// Prototypes
bool         load(const char *dictionary);
unsigned int size(void);
bool         check(const char *word);
bool         unload(void);
int          has_children(node *ptr);
char         tochar(int index);
unsigned int toindex(char c);

#endif // DICTIONARY_H
