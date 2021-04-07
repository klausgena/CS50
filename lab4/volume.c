// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t SAMPLE; // doordat ik eerst uint had gebruikt (unsigned), veroorzaakte ik de distortion (alles positief)

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    // Copy header from input file to output file
    BYTE header[HEADER_SIZE]; // bytes zijn geen gewone ints...
    // read header into memory
    fread(header, sizeof(BYTE), 44, input);
    fwrite(header, sizeof(BYTE), 44, output);
    // read data into memory
    SAMPLE buffer;
    while (fread(&buffer, sizeof(SAMPLE), 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }

    fclose(input);
    fclose(output);
}