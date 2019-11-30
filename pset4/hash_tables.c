#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

enum alphabet
{
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z
};

typedef struct name_list
{
    char *            n;
    struct name_list *next;
} name_list;

int main(void)
{
    name_list *names[ALPHABET_SIZE] = { 0 };

    while (true)
    {
        // get input
        string name = get_string("name: ");
        size_t first_letter = tolower(name[0]) - 'a';

        // no input breaks loop
        if (!strcmp(name, ""))
        {
            break;
        }

        // temporary storage for nesxt name_list
        name_list *na = malloc(sizeof(name_list));
        // check if malloc succeed
        if (!na)
        {
            fprintf(stderr, "could not allocate memory sizeof %ld",
                    sizeof(name_list));
            return 1;
        }

        // update values for temporary storage
        na->n = name;
        na->next = NULL;

        // already has elements
        if (names[first_letter])
        {
            // iterate through name_lists
            for (name_list *ptr = names[first_letter]; ptr != NULL;
                 ptr = ptr->next)
            {
                // one last name_list is found
                if (!ptr->next)
                {
                    // set last name_list next value to temporary name_list
                    ptr->next = na;
                    break;
                }
            }
        }
        else // first element
        {
            // set first name_list
            names[first_letter] = na;
        }
    }

    // print each name_list value, and next name_list address
    for (int alph = 0; alph < ALPHABET_SIZE; ++alph)
    {
        printf("letter %c\n", alph + 'a');
        for (name_list *ptr = names[alph]; ptr != NULL; ptr = ptr->next)
        {
            printf("    value: %s, next address %p\n", ptr->n,
                   (void *)ptr->next);
        }
    }

    // while ptr points to real memory
    for (size_t alph = 0; alph < ALPHABET_SIZE; ++alph)
    {
        // create an name_list iterator for numbers
        name_list *ptr = names[alph];
        while (ptr)
        {
            // store next name_list value
            name_list *next = ptr->next;
            // free current memory
            free(ptr);
            // set up for next loop
            ptr = next;
        }
    }

    return 0;
}
