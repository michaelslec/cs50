#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// essentially unsigned char
typedef uint8_t BYTE;

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

    const size_t kbuffer_size = 512; // bytes in a block of FAT memory
    size_t       image_count = 0; // num of jpg's found
    BYTE         buffer[kbuffer_size]; // buffer for one block of FAT memory
    char         filename[8]; // storage for filename 00x.jpg + \0
    FILE *       img = NULL;

    // eof < 512, so read until can't read 512
    while (fread(buffer, sizeof(BYTE), kbuffer_size, inptr) == kbuffer_size)
    {
        bool jpg_header_found = buffer[0] == 0xff && buffer[1] == 0xd8
                                && buffer[2] == 0xff
                                && (buffer[3] & 0xf0) == 0xe0;

        if (jpg_header_found && img != NULL)
        {
            fclose(img);
            ++image_count;
        }

        if (jpg_header_found)
        {
            sprintf(filename, "%03zd.jpg", image_count);
            img = fopen(filename, "w");
        }

        if (img != NULL)
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
