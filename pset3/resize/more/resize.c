// Copies a BMP file

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy f infile outfile\n");
        return 1;
    }

    // remember filenames & int
    float res_factor = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0) 
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int orig_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // save original height and width for nearest-neighbor
    LONG orig_height = bi.biHeight;
    LONG orig_width = bi.biWidth;

    // calculate new height and width
    bi.biHeight *= res_factor;
    bi.biWidth *= res_factor;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // recalculate header size information
    bi.biSizeImage = (sizeof(RGBTRIPLE) * bi.biWidth + padding) 
                     * abs(bi.biHeight);

    bf.bfSize = sizeof(BITMAPFILEHEADER) 
                + sizeof(BITMAPINFOHEADER) 
                + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    double x_ratio = (float)orig_width / bi.biWidth;
    double y_ratio = fabs((float)orig_height / bi.biHeight);
    int px, py, neighbor_coefficient;

    // iterate through new file scanlines
    // NOTE: biHeight is negative
    printf("bi.biHeight: %d", abs(bi.biHeight));
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        // iterate through RGB bytes
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary RGB storate
            RGBTRIPLE temp;

            // ratio multiplier for nearest neighbor
            px = j * x_ratio;
            py = i * y_ratio;
            neighbor_coefficient = sizeof(RGBTRIPLE) 
                                   * (py * orig_width + px) 
                                   * + (orig_padding * py);

            // location of nearest neighbor in original file
            int nearest_neighbor = sizeof(BITMAPFILEHEADER)
                                   + sizeof(BITMAPINFOHEADER)
                                   + neighbor_coefficient;

            // navigate to nearest neighbor in original file
            fseek(inptr, nearest_neighbor, SEEK_SET);

            // Read RGB from file, then write to new file
            fread(&temp, sizeof(RGBTRIPLE), 1, inptr);
            fwrite(&temp, sizeof(RGBTRIPLE), 1, outptr);
        }

        // then add it back to the output file (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
