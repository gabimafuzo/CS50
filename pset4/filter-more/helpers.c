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
            float red =  image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;

            int average = round((blue + red + green) / 3);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = average;
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
                        counter ++;
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
            image[i][j].rgbtRed =  temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height + 2][width + 2];

    // New image all black
    for (int i = 0; i < height + 2 ; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            new_image[i][j].rgbtBlue = 0;
            new_image[i][j].rgbtGreen = 0;
            new_image[i][j].rgbtRed = 0;
        }
    }

    // Copy original image to new one, leaving borders black
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i + 1][j + 1] = image[i][j];
        }
    }

    // Defining the kernel
    int X_kernel[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Y_kernel[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    // Matrix for storing the new image values
    RGBTRIPLE result[height][width];

    // Iterating through the new image
    for (int i = 1; i <= height; i++)
    {
        for (int j = 1; j <= width; j++)
        {
            float RED_GY = 0, RED_GX = 0, GREEN_GX = 0, GREEN_GY = 0, BLUE_GX = 0, BLUE_GY = 0;

            // Iterating through a 3x3 matrix around the pixel

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int desloci = i + di;
                    int deslocj = j + dj;

                    // Applying the Kernel

                    RED_GX += new_image[desloci][deslocj].rgbtRed * X_kernel[di + 1][dj + 1];
                    RED_GY += new_image[desloci][deslocj].rgbtRed * Y_kernel[di + 1][dj + 1];

                    GREEN_GX += new_image[desloci][deslocj].rgbtGreen * X_kernel[di + 1][dj + 1];
                    GREEN_GY += new_image[desloci][deslocj].rgbtGreen * Y_kernel[di + 1][dj + 1];

                    BLUE_GX += new_image[desloci][deslocj].rgbtBlue * X_kernel[di + 1][dj + 1];
                    BLUE_GY += new_image[desloci][deslocj].rgbtBlue * Y_kernel[di + 1][dj + 1];

                }
            }

            // Applying the Sobel function
            int G_RED = round(sqrt((RED_GX * RED_GX) + RED_GY * RED_GY));
            int G_GREEN = round(sqrt(GREEN_GX * GREEN_GX + GREEN_GY * GREEN_GY));
            int G_BLUE = round(sqrt(BLUE_GX * BLUE_GX + BLUE_GY * BLUE_GY));

            // Rounding G to the range 0 to 255 and updating the resulting pixel (adjusting the index)
            result[i - 1][j - 1].rgbtRed = G_RED > 255 ? 255 : G_RED;
            result[i - 1][j - 1].rgbtGreen = G_GREEN > 255 ? 255 : G_GREEN;
            result[i - 1][j - 1].rgbtBlue = G_BLUE > 255 ? 255 : G_BLUE;
        }
    }

    // Transfers the temporary values to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = result[i][j].rgbtBlue;
            image[i][j].rgbtGreen = result[i][j].rgbtGreen;
            image[i][j].rgbtRed =  result[i][j].rgbtRed;
        }
    }
    return;
}
