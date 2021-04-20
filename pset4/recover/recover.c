#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool check_signature(BYTE *block);

int main(int argc, char *argv[])
{
    // exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // is file readable?
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }
    // allocate 512 BYTES
    BYTE(*block)[512] = calloc(512, sizeof(BYTE));
    if (block == NULL)
    {
        fprintf(stderr, "Memory error.\n");
        return 1;
    }
    // read block into memory
    // count all positives, for naming purposes
    int count = 0;
    bool is_first = true;
    char filename[8];
    FILE *filenamepointer = NULL;
    while (fread(block, 512 * sizeof(BYTE), 1, file) == 1)
    {
        // check if block begins with signature
        if (check_signature(*block))
        {
            // check if we are already writing a file
            // if not, create new file and write. If yes,
            // close old file and then create new file and write.
            if (is_first == true)
            {
                is_first = false;
            }
            else
            {
                fclose(filenamepointer);
            }
            sprintf(filename, "%03d.jpg", count);
            filenamepointer = fopen(filename, "w");
            if (filenamepointer == NULL)
            {
                fclose(filenamepointer);
                fprintf(stderr, "Could not create file.\n");
            }
            //  open new outfile and add block
            fwrite(block, 512 * sizeof(BYTE), 1, filenamepointer);
            count++;
        }
        // block does not start with signature
        else
        {
            if (is_first == false)
            {
                // append block to existing file
                fwrite(block, 512 * sizeof(BYTE), 1, filenamepointer);
            }
        }
    }
    fclose(filenamepointer);
    free(block);
    return 0;
}

// helper function
bool check_signature(BYTE *block)
{
    // check first 4 bytes
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
    {
        if (block[3] <= 0xef && block[3] >= 0xe0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}