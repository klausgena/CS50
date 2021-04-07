// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef uint16_t SAMPLE;

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
    // TODO: Copy header from input file to output file
    // van factorize een functie maken met een pointer als arg
    // van buffer een malloc maken, om te testen
    BYTE header[HEADER_SIZE]; // bytes zijn geen gewone ints...
    // read header into memory
    int header_size = fread(header, sizeof(BYTE), 44, input);
    // header 41-44 contain the size of the data part
    uint32_t data_size = header[40] + (header[41] << 8) + (header[42] << 16) + (header [43] << 24);
    SAMPLE buffer[data_size/2];
    // read data into memory
    fseek(input, 44, SEEK_SET);
    int check_data_size = fread(buffer, sizeof(SAMPLE), data_size/2, input);
// Morgen alles herschrijven met behulp van fseek...

    fwrite(header, sizeof(BYTE), 44, output);
    fseek(output, 44, SEEK_SET);
    fwrite(buffer, sizeof(SAMPLE), data_size/2, output);
    // tests
    printf("Header size and data size: %i and %u or %u\n", header_size, data_size, check_data_size);
    // factorize the samples...
    // TODO: Read samples from input file and write updated data to output file
    // while(fread(&buffer, sizeof(struct wav), 1, input))
    // {
    //     fwrite(&buffer, sizeof(SAMPLE), 1, output);
    // }
    // // Close files
    // fclose(input);
    // fclose(output);
}
