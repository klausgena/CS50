#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   // for every pixe (RGBTRIPLE) in image
   for (int i = 0; i < height ; i++)
   {
       for (int j = 0; j < width; j++)
       {
            RGBTRIPLE* pixel = image[i]; // de pointer is de rij
            // int32_t blue = (int32_t)pixel[j].rgbtBlue;
            // int32_t red = (int32_t)pixel[j].rgbtRed;
            // int32_t green = (int32_t)pixel[j].rgbtGreen;
            int blue = pixel[j].rgbtBlue;
            int red = pixel[j].rgbtRed;
            int green = pixel[j].rgbtGreen;
            // make a sum of all three colors
            // calculate the average
            int average = (blue + red + green) / 3;
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
