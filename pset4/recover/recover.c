#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    char *file = argv[1];

    // Open the memory card
    FILE *card = fopen(file, "r");

    if (!card)
    {
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    char filename[8]; // ###.jpg\0
    FILE *img = NULL; // Pointer to JPEG file
    int counter = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        // Checks if the buffer can be the start of a JPEG
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If there is already a JPEG file open, close it
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a name for my file
            sprintf(filename, "%03i.jpg", counter);

            // Open file for writing
            img = fopen(filename, "w");

            if (img == NULL)
            {
                fclose(card);
                return 1;
            }
            counter++;
        }

        // If there's an open JPEG file, write the current block of data to it
        if (img != NULL)
        {
            // Check if it was written correctly
            if (fwrite(buffer, 1, 512, img) != 512)
            {
                fclose(img);
                fclose(card);
                return 1;
            }
        }
    }

    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(card);
}
