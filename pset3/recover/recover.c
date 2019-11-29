#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file.jpg\n");
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

    const size_t  kbuffer_size = 512; // bytes in a block of FAT memory
    size_t        nth_jpg      = 0; // num of jpg's found
    unsigned char buffer[kbuffer_size];

    // eof < 512, so read until can't read 512
    while (fread(buffer, sizeof(char), kbuffer_size, inptr) == kbuffer_size)
    {
        // check for start of jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            ++nth_jpg;
        }
    }

    printf("%zd JPG's found\n", nth_jpg);

    // close file to recover
    fclose(inptr);

    return 0;
}
