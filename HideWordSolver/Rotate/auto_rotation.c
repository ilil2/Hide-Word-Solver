#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include "../ANNA_graphics.h"
#include "rotation.h"
#include "../Preprocessing/medianfilter.h"

SDL_Surface* preprocess_image(SDL_Surface* surface)
{
    surface_to_grayscale(surface);

    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    Uint8 threshold = otsus(len, pixels, surface->format);
	surface_to_black_and_white(surface, threshold);
    median_filter(surface);

    Uint32* result = malloc(len * sizeof(Uint32));
    if (result == NULL)
        errx(EXIT_FAILURE, "Memory allocation failed");

    //sobel(surface, result);

    //memcpy(surface->pixels, result, len * sizeof(Uint32));

    //free(result);

    return surface;
}

void auto_rotate(const char* image_path)
{
    SDL_Surface* surface = IMG_Load(image_path);
    if (!surface)
        errx(EXIT_FAILURE, "Image loading failed: %s", IMG_GetError());

    SDL_Surface* preprocessed_surface = preprocess_image(surface);
    double angle = detectRotationAngle(preprocessed_surface);
    
    display_image(image_path, angle);

    SDL_FreeSurface(surface);
}
