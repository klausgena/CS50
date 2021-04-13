#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
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

// Blur image.
// TODO: watch video, check border cases, check averages.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int h, v, mv, mh;
    // create copy of original picture
    RGBTRIPLE (*imagecopyarr)[height];
    imagecopyarr = malloc(sizeof(*imagecopyarr) * width);
    memcpy(&imagecopyarr[0][0], &image[0][0], sizeof(image[0][0]) * height * width);
    // THAT WAS NOT EASY!!! Have to do pointer exercices to get the hang of it!
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
                v = 0; // instead of -1
            else
                v = -1;
            if (j == 0)
                h = 0; // instead of -1
            else
                h = -1;
            if (i == height - 1)
                mv = 0;
            else
                mv = 1;
            if (j == width - 1) // AM I WRONG HERE?
                mh = 0; // instead of 1
            else
                mh = 1;
            float all_red = 0, all_blue = 0, all_green = 0;
            int average_blue = 0, average_red = 0, average_green = 0;
            int count = 0;
            // I have to pass the value of i and j to select the right pixels
            // but I also have to offset the other values...
            int k, l;
            for (k = i + v; k <= mv + i; k++)
            {
                for (l = j + h; l <= mh + j; l++)
                {
                    RGBTRIPLE pixel = imagecopyarr[k][l];
                    all_red = pixel.rgbtRed + all_red;
                    all_blue = pixel.rgbtBlue + all_blue;
                    all_green = pixel.rgbtGreen + all_green;
                    count ++;
                }
            }
            average_blue = round(all_blue / count);
            average_red = round(all_red / count);
            average_green = round(all_green / count);
            // MIJN PROBLEEM: DON'T CHANGE THE IMAGE ITSELF, BUT IMPLEMENT THE
            // CHANGE IN A COPY OF THE IMAGE...(OR GET THE DATA FROM AN
            // UNTOUCHED OLD Copy). Here we need malloc...
            RGBTRIPLE* pixelrow = image[i];
            pixelrow[j].rgbtRed = average_red;
            pixelrow[j].rgbtBlue = average_blue;
            pixelrow[j].rgbtGreen = average_green;
        }
    }
    free(imagecopyarr);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}