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
            RGBTRIPLE *pixel = image[i]; // de pointer is de rij
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
            RGBTRIPLE *left_address = *(image + i) + j;
            RGBTRIPLE *right_address = *(image + i) + (width - j - 1);
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
    RGBTRIPLE(*imagecopyarr)[width];
    imagecopyarr = malloc(sizeof(*imagecopyarr) * height);
    if (imagecopyarr == NULL)
    {
        return;
    }
    memcpy(&imagecopyarr[0][0], &image[0][0], sizeof(image[0][0]) * height * width);
    // THAT WAS NOT EASY!!! Have to do pointer exercices to get the hang of it!
    // REWRITE WITH COPY IN MIND
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
            {
                v = 0;// instead of -1
            }
            else
            {
                v = -1;
            }
            if (j == 0)
            {
                h = 0;// instead of -1
            }
            else
            {
                h = -1;
            }
            if (i == height - 1)
            {
                mv = 0;
            }
            else
            {
                mv = 1;
            }
            if (j == width - 1)
            {
                mh = 0;
            }
            else
            {
                mh = 1;
            }
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
            RGBTRIPLE *pixelrow = image[i];
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
    // copy image
    RGBTRIPLE(*image_copy)[width];
    image_copy = malloc(sizeof(*image_copy) * height);
    if (image_copy == NULL)
    {
        return;
    }
    memcpy(&image_copy[0][0], &image[0][0], sizeof(image[0][0]) * height * width);
    // loop over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize arrays for Gx and Gy
            int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
            int redGx = 0, blueGx = 0, greenGx = 0;
            int redGy = 0, blueGy = 0, greenGy = 0;
            int pixnum = 0;
            for (int k = -1 + i; k <= 1 + i ; k++)
            {
                for (int l = -1 + j; l <= 1 + j; l++)
                {
                    // get RGB values for pixels
                    // but not if outside image boundaries
                    if (k == -1 || l == -1 || k == height || l == width)
                    {
                        pixnum++;
                        continue;
                    }
                    else
                    {
                        RGBTRIPLE pixel = image_copy[k][l];
                        redGx =  redGx + pixel.rgbtRed * Gx[pixnum];
                        greenGx = greenGx + pixel.rgbtGreen * Gx[pixnum];
                        blueGx = blueGx + pixel.rgbtBlue * Gx[pixnum];
                        redGy = redGy + pixel.rgbtRed * Gy[pixnum];
                        blueGy = blueGy + pixel.rgbtBlue * Gy[pixnum];
                        greenGy = greenGy + pixel.rgbtGreen * Gy[pixnum];
                        pixnum++;
                    }
                }
            }
            // calculate sobel nr.
            RGBTRIPLE *pixelrow = image[i];
            int sobel_red = round(sqrt((redGx * redGx) + (redGy * redGy)));
            int sobel_blue = round(sqrt((blueGx * blueGx) + (blueGy * blueGy)));
            int sobel_green = round(sqrt((greenGx * greenGx) + (greenGy * greenGy)));
            // WARNING
            if (sobel_red <= 255)
            {
                pixelrow[j].rgbtRed = sobel_red;
            }
            else
            {
                pixelrow[j].rgbtRed = 255;
            }
            if (sobel_green <= 255)
            {
                pixelrow[j].rgbtGreen = sobel_green;
            }
            else
            {
                pixelrow[j].rgbtGreen = 255;
            }
            if (sobel_blue <= 255)
            {
                pixelrow[j].rgbtBlue = sobel_blue;
            }
            else
            {
                pixelrow[j].rgbtBlue = 255;
            }
        }
    }
    free(image_copy);
    return;
}