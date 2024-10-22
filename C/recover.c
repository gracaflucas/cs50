#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check the first 3 bytes, if 0xff 0xd8 0xff, is a JPEG
    // the 4th byte first 4 bits is 1110
    // can check slack space, the 1.048.576 byte.
    // when you find a JPEG signature, open a new file and write the bytes
    // when encountering another signature, close older file and open another new file
    // for efficiency, check every 512bytes (or a block), if not a JPEG, next block, so on and so on
    // only accept 1 command line argument
    // if incorrect use, remind correct usage and return 1
    // if forensic image cannot be opened for reading, return 1 and inform user
    // new files should be named ###.jpg, where ### is count from 000 up.
    if (argc != 2)
    {
        printf("usage: ./recover FILE\n");
        return (1);
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file\n");
        return (1);
    }
    BYTE buffer[BLOCK_SIZE];
    char filename[8];
    FILE *image = NULL;
    int n = 0;

    while (fread(buffer, 1, BLOCK_SIZE, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (n != 0)
                fclose(image);
            sprintf(filename, "%03i.jpg", n++);
            image = fopen(filename, "w");
            fwrite(buffer, BLOCK_SIZE, 1, image);
        }
        else if (image != NULL)
            fwrite(buffer, BLOCK_SIZE, 1, image);
    }
    if (image != NULL)
        fclose(image);
    fclose(card);
}
