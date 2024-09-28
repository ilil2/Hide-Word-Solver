#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>
#include "rotation.h"


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
