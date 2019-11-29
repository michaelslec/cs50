#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file.jpeg\n");
        return 1;
    }

    // remember files names
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }

    return 0;
}
