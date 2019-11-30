#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int          n;
    struct node *next;
} node;

int main(void)
{
    node *numbers = NULL;

    while (true)
    {
        // get input
        int number = get_int("Number: ");

        // allows ctrl-d to exit while loop
        if (number == INT_MAX)
        {
            break;
        }

        // temporary storage for nesxt node
        node *n = malloc(sizeof(node));
        // check if malloc succeed
        if (!n)
        {
            return 1;
        }

        // update values for temporary storage
        n->n = number;
        n->next = NULL;

        // already has elements
        if (numbers)
        {
            // iterate through nodes
            for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
            {
                // one last node is found
                if (!ptr->next)
                {
                    // set last node next value to temporary node
                    ptr->next = n;
                    break;
                }
            }
        }
        else // first element
        {
            // set first node
            numbers = n;
        }
    }

    // print each node value, and next node address
    for (node *ptr = numbers; ptr != NULL; ptr = ptr->next)
    {
        printf("value: %d, next address %p\n", ptr->n, (void *)ptr->next);
    }

    // create an node iterator for numbers
    node *ptr = numbers;
    // while ptr points to real memory
    while (ptr)
    {
        // store next node value
        node *next = ptr->next;
        // free current memory
        free(ptr);
        // set up for next loop
        ptr = next;
    }

    return 0;
}
