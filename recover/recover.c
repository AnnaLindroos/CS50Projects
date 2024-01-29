#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Number of bytes in each block
const int BLOCK_SIZE = 512;

// A type to store a byte of data
typedef uint8_t BYTE;

// A boolean to determine if a block is a jpg
bool is_jpg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE \n");
        return 1;
    }
    //Open forsenic image
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Allocate memory for buffer
    BYTE buffer[512];

    //JPG counter
    int jpg_count = 000;
    // image pointer
    FILE *img = NULL;

    // Read 512 bytes into the buffer
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        //If start of new jpg
        if (is_jpg(buffer) == true)
        {
            char name[8];

            if (img != NULL)
            {
                // Close the handle to old file
                fclose(img);
            }

            // Create string with sprint to store jpg filename
            sprintf(name, "%03i.jpg", jpg_count);

            // Open a handle to the current filename
            img = fopen(name, "w");
            // Write data from memory to filename
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);

            jpg_count++;
        }
        else if (img != NULL)
        {
            // Write data from memory to filename.
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }

    }

    fclose(img);

    // close remaining files
    fclose(card);
}


bool is_jpg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}