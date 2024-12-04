#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stdlib.h>
#include "rotation.h"
#include "../Preprocessing/medianfilter.h"

void auto_rotate(const char* image_path)
{
    SDL_Surface* surface = IMG_Load(image_path);
    if (!surface)
        errx(EXIT_FAILURE, "Image loading failed: %s", IMG_GetError());

    double angle = detectRotationAngle(surface);
    printf("%f", angle);

    SDL_FreeSurface(surface);

    display_image(image_path, angle);
}
