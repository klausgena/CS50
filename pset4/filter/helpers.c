#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   // for every pixe (RGBTRIPLE) in image
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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
