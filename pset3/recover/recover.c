#include <stdbool.h>
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
    unsigned char buffer[kbuffer_size]; // buffer for one block of FAT memory
    char          filename[8]; // storage for filename 00x.jpg + \0
    bool          file_open = 0; // is a jpg already open?
    FILE *        img;

    // eof < 512, so read until can't read 512
    while (fread(buffer, sizeof(char), kbuffer_size, inptr) == kbuffer_size)
    {
        // check for start of jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff
            && (buffer[3] & 0xf0) == 0xe0)
        {
            // if a file is already open && there's a new jpg header
            if (file_open)
            {
                fclose(img);
                sprintf(filename, "%03zd.jpg", nth_jpg);
                img = fopen(filename, "w");
                fwrite(buffer, kbuffer_size, 1, img);
                ++nth_jpg;
            }
            // first jpg found
            else
            {
                file_open = 1;
                sprintf(filename, "%03zd.jpg", nth_jpg);
                img = fopen(filename, "w");
                fwrite(buffer, kbuffer_size, 1, img);
                ++nth_jpg;
            }
        }
        // file is already open, and its not the start of another jpg
        else if (file_open)
        {
            fwrite(buffer, kbuffer_size, 1, img);
        }
    }

    // close file to recover
    fclose(inptr);

    // close image file
    fclose(img);

    return 0;
}
