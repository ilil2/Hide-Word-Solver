#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>
#include "rotation.h"

double detectRotationAngle(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;

    double* gradient_x = (double*)malloc(width * height * sizeof(double));
    double* gradient_y = (double*)malloc(width * height * sizeof(double));
    double* angles = (double*)malloc(width * height * sizeof(double));

    int sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int sobel_y[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            double gx = 0;
            double gy = 0;

            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    Uint32 pixel = *((Uint32*)image->pixels + (y + ky) * width + (x + kx));
                    Uint8 r, g, b;
                    SDL_GetRGB(pixel, image->format, &r, &g, &b);
                    double intensity = 0.299 * r + 0.587 * g + 0.114 * b;

                    gx += sobel_x[ky + 1][kx + 1] * intensity;
                    gy += sobel_y[ky + 1][kx + 1] * intensity;
                }
            }

            gradient_x[y * width + x] = gx;
            gradient_y[y * width + x] = gy;
            angles[y * width + x] = atan2(gy, gx) * (180.0 / M_PI);
        }
    }

    double total_angle = 0;
    int count = 0;

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            if (gradient_x[y * width + x] != 0 || gradient_y[y * width + x] != 0)
            {
                total_angle += angles[y * width + x];
                count++;
            }
        }
    }

    double average_angle = count > 0 ? total_angle / count : 0;

    free(gradient_x);
    free(gradient_y);
    free(angles);

    return average_angle;
}

void auto_rotate(const char* image_path)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("Error initializing SDL_image: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Surface* image = IMG_Load(image_path);
    if (!image)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return;
    }

    double angle = detectRotationAngle(image);
    display_image(image_path, angle); 

    SDL_FreeSurface(image);
    IMG_Quit();
    SDL_Quit();
}
