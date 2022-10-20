#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            long grey = (long)round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avgcountr;
    float Blue;
    float Red;
    float Green;

    RGBTRIPLE image2[height][width]; // copy of original image

    // copying pixels from original image to our copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image2[i][j] = image[i][j];
        }
    }

    //  Iterating through image pixels
    for (int i = 0; i < height; i++) // iterating over rows
    {
        for (int j= 0; j < width; j++) // iterating over columns
        {
            Blue = Red = Green = 0; // setting colour zero before moving to a pixel
            avgcountr = 0; // resetting colour before moving to a pixel

    //------Iterating over 3*3 box to calculate average
            for (int k = -1; k < 2; k++) // for box rows
            {
                for (int l = -1; l < 2; l++) // box columns
                {
                    // Checking if pixel from 3*3 box lies inside image
                    // if it does, skip that pixel from average
                    if (i + k < 0 || i + k > height - 1 || j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    Blue += image2[i+k][j+l].rgbtBlue;
                    Green += image2[i+k][j+l].rgbtGreen;
                    Red += image2[i+k][j+l].rgbtRed;
                    avgcountr++;
                }
            }
            // updating values in the original image.
            image[i][j].rgbtBlue = round(Blue / avgcountr);
            image[i][j].rgbtGreen = round(Green / avgcountr);
            image[i][j].rgbtRed = round(Red / avgcountr);

        }
    }
}
