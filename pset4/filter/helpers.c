#include "helpers.h"
#include <math.h>
#include <stdlib.h>
// helper function
void average_surrounding_pixels(RGBTRIPLE image[h][v], int c, int h, int v, int c2);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   // for every pixel (RGBTRIPLE) in image
   for (int i = 0; i < height ; i++)
   {
       for (int j = 0; j < width; j++)
       {
            RGBTRIPLE* pixel = image[i]; // de pointer is de rij
            int blue = pixel[j].rgbtBlue;
            int red = pixel[j].rgbtRed;
            int green = pixel[j].rgbtGreen;
            // make a sum of all three colors
            // calculate the average
            int average = roundf((float)(blue + red + green) / 3.0);
            // insert this average in all three colors
            pixel[j].rgbtBlue = average;
            pixel[j].rgbtRed = average;
            pixel[j].rgbtGreen = average;
       }
   }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int j = 0; // waarom 1 en geen 0?
        // move every pixel in the row to it's opposite position
        while (j < (width / 2))
        {
            RGBTRIPLE* left_address = *(image + i) + j;
            RGBTRIPLE* right_address = *(image + i) + (width - j - 1);
            RGBTRIPLE tmp = *left_address;
            // swap content
            *left_address = *right_address;
            *right_address = tmp;
            j++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // for loop for every pixel
    // a list of conditions
    // in every condition a call to average_surrounding_pixels
    // with the correct counters and offsets.
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
// helper function to calculate averages and assign them to the pixels
void average_surrounding_pixels(int c, int h, int v, int c2) // ik moet de pixel doorgeven aan de functie!!!!
// hierover nadenken
// TODO: ofwel in de condities de verschillende h v en c toewijzen!! en deze functie niet gebruiken.
{
    float all_red = 0, all_blue = 0, all_green = 0;
    int count = 0;
    for (int i = h; i <= c; i++)
    {
        for (int j = v, j <= c2; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            all_red = pixel.rgbtRed + all_red;
            all_blue = pixel.rgbtBlue + all_blue;
            all_green = pixel.rgbtGreen + all_green;
            count ++;
        }
    }
    // assigning should also be a for loop, because we need the averages
    int average_blue = roundf(all_blue / (float)count);
    int average_red = roundf(all_red) / (float)count);
    int average_green = roundf(all_green) / (float)count);

    for (int i = h; i <= c; i++)
    {
        RGBTRIPLE* pixelrow = image[i];
        for (int j = v, j <= c2; j++)
        {
            // assign every pixel color its average
            // make a loop over an array with RGB?
            pixelrow[j].rgbtRed = average_red;
            pixelrow[j].rgbtBlue = average_blue;
            pixelrow[j].rgbtGreen = average_green;
        }
    }
    return;
}