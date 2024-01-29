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
            // Calculate new pixel colors
            int new = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));
            image[i][j].rgbtRed = new;
            image[i][j].rgbtGreen = new;
            image[i][j].rgbtBlue = new;
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
            // Set the original values to each pixel
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Calculate new red
            int sepiaRed = round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }

            // Calculate new green
            int sepiaGreen = round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            // Calculate new blue
            int sepiaBlue = round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }

            // Set the new pixel values to the original picture
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Create swap function
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    BYTE temp_red = a->rgbtRed;
    a->rgbtRed = b->rgbtRed;
    b->rgbtRed = temp_red;

    BYTE temp_green = a->rgbtGreen;
    a->rgbtGreen = b->rgbtGreen;
    b->rgbtGreen = temp_green;

    BYTE temp_blue = a->rgbtBlue;
    a->rgbtBlue = b->rgbtBlue;
    b->rgbtBlue = temp_blue;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over half of the picture and swap values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - (j + 1)]);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy image into copy
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // create neighbors for each pixel
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            int validNeighbors = 0;

            // Before getting neighbors
            for (int yOffset = y - 1; yOffset <= y + 1; yOffset++)
            {
                for (int xOffset = x - 1; xOffset <= x + 1; xOffset++)
                {
                    // Handle corner-cases
                    if (xOffset < 0 || yOffset < 0)
                    {
                        continue;
                    }
                    else if (xOffset >= width || yOffset >= height)
                    {
                        continue;
                    }

                    RGBTRIPLE neighbor = copy[yOffset][xOffset];
                    // Add values
                    red += neighbor.rgbtRed;
                    green += neighbor.rgbtGreen;
                    blue += neighbor.rgbtBlue;
                    validNeighbors++;

                }
            }
            // Calculate new values
            int averageRed = round((float)red / validNeighbors);
            int averageGreen = round((float)green / validNeighbors);
            int averageBlue = round((float)blue / validNeighbors);

            image[y][x].rgbtRed = averageRed;
            image[y][x].rgbtGreen = averageGreen;
            image[y][x].rgbtBlue = averageBlue;
            // After getting neighbors
        }
    }
}
