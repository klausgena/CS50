#include "helpers.h"
#include <math.h>
#include <stdlib.h>
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

// Blur image. Aha : Maar 1 pixel krijgt die average values!!!
// TODO: watch video, check border cases, check averages.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h, v, m;
    // for loop for every pixel
    // in every condition a call to average_surrounding_pixels
    // with the correct counters and offsets.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // a list of conditions for corner cases: top row, left and right
            // rows, last row.
            if (i == 0)
                h = 0; // instead of -1
            else
                h = -1;
            if (j == 0)
                v = 0; // instead of -1
            else
                v = -1;
            if (i == height - 1 || j == width - 1) // AM I WRONG HERE?
                m = 0; // instead of 1
            else
                m = 1;
            float all_red = 0, all_blue = 0, all_green = 0;
            int count = 0;
            // I have to pass the value of i and j to select the right pixels
            // but I also have to offset the other values...
            int k, l;
            for (k = i + h; k <= m + i; k++)
            {
                for (l = j + v; l <= m + j; l++)
                {
                    RGBTRIPLE* pixel = image[k];
                    all_red = pixel[l].rgbtRed + all_red;
                    all_blue = pixel[l].rgbtBlue + all_blue;
                    all_green = pixel[l].rgbtGreen + all_green;
                    count ++;
                }
            }
            int average_blue = round(all_blue / count);
            int average_red = round(all_red / count);
            int average_green = round(all_green / count);
            // k and l need to be reset
            // THIS LOOOP IS NOT NEEDED: ONLY ASSIGN THE AVERAGE TO ONE PIXEL!
            for (k = i + h; k <= m + i; k++)
            {
                RGBTRIPLE* pixelrow = image[k];
                for (l = j + v; l <= m + j; l++)
                {
                    // assign every pixel color its average
                    pixelrow[l].rgbtRed = average_red;
                    pixelrow[l].rgbtBlue = average_blue;
                    pixelrow[l].rgbtGreen = average_green;
                }
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}