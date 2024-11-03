#include "ANNA_graphics.h"

SDL_Surface* preprocess_image(SDL_Surface* surface)
{
    surface_to_grayscale(surface);

    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    Uint8 threshold = otsus(len, pixels, surface->format);
        surface_to_black_and_white(surface, threshold);
    //median_filter(surface);

    Uint32* result = malloc(len * sizeof(Uint32));
    if (result == NULL)
        errx(EXIT_FAILURE, "Memory allocation failed");

    return surface;
}
