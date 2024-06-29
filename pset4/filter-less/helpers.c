#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;

            int average = round((blue + red + green) / 3);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Matrix to store the new image values
    RGBTRIPLE temp[height][width];

    int sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue);

            // Rounding the sepiacolor to the range 0 to 255
            temp[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            temp[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            temp[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }

    // Transfers the temporary values to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
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
    // Matrix to store the new image values
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float totalRed = 0, totalGreen = 0, totalBlue = 0, counter = 0;

            // Iterating through a 3x3 matrix around the pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int desloci = i + di;
                    int deslocj = j + dj;

                    // Checks if the shifts are within the image bounds

                    if (desloci >= 0 && desloci < height && deslocj >= 0 && deslocj < width)
                    {
                        totalRed += image[desloci][deslocj].rgbtRed;
                        totalGreen += image[desloci][deslocj].rgbtGreen;
                        totalBlue += image[desloci][deslocj].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Average of the pixel colors
            int averageRed = round(totalRed / counter);
            int averageGreen = round(totalGreen / counter);
            int averageBlue = round(totalBlue / counter);

            // Stores value in the temporary matrix
            temp[i][j].rgbtBlue = averageBlue;
            temp[i][j].rgbtGreen = averageGreen;
            temp[i][j].rgbtRed = averageRed;
        }
    }

    // Transfers the temporary values to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}
