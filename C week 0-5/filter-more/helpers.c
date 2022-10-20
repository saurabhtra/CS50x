#include "helpers.h"
#include <math.h>

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
        for (int j = 0; j < width; j++) // iterating over columns
        {
            Blue = Red = Green = 0; // setting colour zero before moving to a pixel
            avgcountr = 0;          // resetting colour before moving to a pixel

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
                    Blue += image2[i + k][j + l].rgbtBlue;
                    Green += image2[i + k][j + l].rgbtGreen;
                    Red += image2[i + k][j + l].rgbtRed;
                    avgcountr++;
                }
            }
            // updating values in the original image.
            image[i][j].rgbtBlue = round(Blue / avgcountr);
            image[i][j].rgbtGreen = round(Green / avgcountr);
            image[i][j].rgbtRed = round(Red / avgcountr);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Ask for some temparory memories for store blur pixels
    RGBTRIPLE temp[height][width];

    // Consider every condition you may encounter with pixels
    int GxR, GyR, GxG, GyG, GxB, GyB;

    // Initialize Gx and Gy metrix
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxR = GyR = GxG = GyG = GxB = GyB = 0;

            // Loop over 3x3 pixels
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    // Check if this pixel is outside the image
                    if (i + h < 0 || i + h > height - 1)
                    {
                        continue;
                    }

                    if (j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }

                    // sum each channel value
                    // X
                    GxR += image[i + h][j + w].rgbtRed * Gx[h + 1][w + 1];
                    GxG += image[i + h][j + w].rgbtGreen * Gx[h + 1][w + 1];
                    GxB += image[i + h][j + w].rgbtBlue * Gx[h + 1][w + 1];

                    // Y
                    GyR += image[i + h][j + w].rgbtRed * Gy[h + 1][w + 1];
                    GyG += image[i + h][j + w].rgbtGreen * Gy[h + 1][w + 1];
                    GyB += image[i + h][j + w].rgbtBlue * Gy[h + 1][w + 1];
                }
            }

            // Calculate every Gx and Gy value and store in temp
            temp[i][j].rgbtRed = fmin(round(sqrt((GxR * GxR + GyR * GyR))), 255);
            temp[i][j].rgbtGreen = fmin(round(sqrt((GxG * GxG + GyG * GyG))), 255);
            temp[i][j].rgbtBlue = fmin(round(sqrt((GxB * GxB + GyB * GyB))), 255);
        }
    }

    // Ready to iterate whole image from temp to image[i][j]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
