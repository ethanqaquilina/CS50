#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgRGB =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avgRGB;
            image[i][j].rgbtGreen = avgRGB;
            image[i][j].rgbtRed = avgRGB;
        }
    }
    return;
}

// Convert image to sepia

void check(int *colorVal);

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculates the Sepia Values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);

            // Checks the values are not greater then 255
            check(&sepiaRed);
            check(&sepiaGreen);
            check(&sepiaBlue);

            // Sets the image values to new values;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // for (int i = 0; i < height/2; i++)
    // {
    //     RGBTRIPLE *temp;
    //     temp = image[i];
    //     *image[i] = image[height-i];
    //     image[height-i] = temp;
    // }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Blur the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixsumR = 0;
            int pixsumG = 0;
            int pixsumB = 0;
            float pixCount = 0;

            // Iterate through a 3x3 around the pixel
            for (int y = i - 1; y < i + 2; y++)
            {
                for (int x = j - 1; x < j + 2; x++)
                {
                    // Check if current pixel is valid
                    if ((y >= 0 && y < height) && (x >= 0 && x < width))
                    {
                        pixsumB += copy[y][x].rgbtBlue;
                        pixsumG += copy[y][x].rgbtGreen;
                        pixsumR += copy[y][x].rgbtRed;
                        pixCount++;
                    }
                }
            }

            // Change original pixel to new vals
            image[i][j].rgbtBlue = round(pixsumB / pixCount);
            image[i][j].rgbtGreen = round(pixsumG / pixCount);
            image[i][j].rgbtRed = round(pixsumR / pixCount);
        }
    }
    return;
}

// Helper function for sepia
void check(int *colorVal)
{
    if (*colorVal > 255)
    {
        *colorVal = 255;
    }
    return;
}
