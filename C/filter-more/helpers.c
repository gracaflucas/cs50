#include "helpers.h"
#include <cs50.h>
#include <math.h>

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // take the average of red, green and blue, to take the black or grayish tone
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // use swap in each pixel
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    float count = 0;
    int sum = 0;
    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int col = j - 1; col <= (j + 1); col++)
        {
            if (row < 0 || row >= height || col < 0 || col >= width)
                continue;
            if (color_position == RED_COLOR)
                sum += image[row][col].rgbtRed;
            else if (color_position == BLUE_COLOR)
                sum += image[row][col].rgbtBlue;
            else
                sum += image[row][col].rgbtGreen;
            count++;
        }
    }
    return round(sum / count);
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // for each color value, give it a new value by averaging the color values of neighboring pixels in a 3x3.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, RED_COLOR);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, BLUE_COLOR);
        }
    }
    return;
}

// Detect edges

int cap(int value)
{
    if (value < 0)
        return 0;
    else if (value > 255)
        return (255);
    else
        return value;
}

RGBTRIPLE getEdge(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int redValueX, redValueY, greenValueX, greenValueY, blueValueX, blueValueY;
    redValueX = redValueY = greenValueX = greenValueY = blueValueX = blueValueY = 0;
    for (int row = -1; row <= 1; row++)
    {
        for (int col = -1; col <= 1; col++)
        {
            int rowIndex = i + row;
            int colIndex = j + col;
            if (rowIndex >= 0 && rowIndex < height && colIndex >= 0 && colIndex < width)
            {
                int x = Gx[row + 1][col + 1];
                redValueX += x * image[rowIndex][colIndex].rgbtRed;
                greenValueX += x * image[rowIndex][colIndex].rgbtGreen;
                blueValueX += x * image[rowIndex][colIndex].rgbtBlue;

                int y = Gx[col + 1][row + 1];
                redValueY += y * image[rowIndex][colIndex].rgbtRed;
                greenValueY += y * image[rowIndex][colIndex].rgbtGreen;
                blueValueY += y * image[rowIndex][colIndex].rgbtBlue;
            }
        }
    }
    RGBTRIPLE pixel;
    pixel.rgbtRed = cap(round(sqrt(redValueX * redValueX + redValueY * redValueY)));
    pixel.rgbtGreen = cap(round(sqrt(greenValueX * greenValueX + greenValueY * greenValueY)));
    pixel.rgbtBlue = cap(round(sqrt(blueValueX * blueValueX + blueValueY * blueValueY)));

    return pixel;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // sobel operator in 3x3.
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = getEdge(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
