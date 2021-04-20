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
   bool file_exists = false;
   char filename[8];
   FILE *filenamepointer = NULL;
   while (fread(block, 512 * sizeof(BYTE), 1, file) == 1)
   {
        // if not first file we write, close previous file
        if (file_exists == true && check_signature(*block))
        {
            fclose(filenamepointer);
            file_exists = false;
        }
        if (file_exists == false && check_signature(*block))
        {
            // create output file
            sprintf(filename, "%03d.jpg", count);
            filenamepointer = fopen(filename, "w");
            if (filenamepointer == NULL)
            {
                fclose(file);
                fprintf(stderr, "Could not create file.\n");
            }
            //  open new outfile and add block
            fwrite(block, 512 * sizeof(BYTE), 1, filenamepointer);
            count++;
            file_exists = true;
        }
        else if (file_exists == true)
        {
            // if signature existed: add block to existing outfile
            fwrite(block, 512 * sizeof(BYTE), 1, filenamepointer);
        }
        // if no signature at beginning of file, keep looking
        else
        {
             continue;
        }
   }
   free(block);
return 0;
}

// helper function
bool check_signature(BYTE *block)
{
    // check first 4 bytes
    if (block[0] != 0xff && block[1] != 0xd8 && block[2] != 0xff)
    {
        return false;
    }
    else if (block[3] > 0xef || block[3] < 0xe0)
    {
       return false;
    }
    else
    {
        printf("We got lucky!\n");
        return true;
    }
}
