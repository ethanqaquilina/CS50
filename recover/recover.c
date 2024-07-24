#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check that greate than one or no command arguement is made
    if (argc != 2)
    {
        printf("Usage: ./recover.c card.raw\n");
        return 1;
    }

    // Check valid file and open
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Buffer byte block
    uint8_t buffer[512];

    // Create first output file
    int JPEGcount = 0;
    char filename[8];
    sprintf(filename, "%03i.jpg", JPEGcount);
    FILE *output = fopen(filename, "w");

    while (fread(buffer, 1, 512, card) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            if (JPEGcount == 0)
            {
                JPEGcount++;
                fwrite(buffer, 1, 512, output);
            }
            else
            {
                // Close current file
                fclose(output);

                // Edit file name for next file;
                sprintf(filename, "%03i.jpg", JPEGcount);

                // Output JPEG byte blocks
                output = fopen(filename, "w");
                JPEGcount++;
                fwrite(buffer, 1, 512, output);
            }
        }
        else if (JPEGcount > 0)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
    fclose(output);
    fclose(card);
}
