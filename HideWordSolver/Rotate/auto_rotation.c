#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
// #include "../ANNA_graphics.h"
#include "rotation.h"
#include "../Preprocessing/medianfilter.h"


void auto_rotate(const char* image_path)
{
    SDL_Surface* surface = IMG_Load(image_path);
    if (!surface)
        errx(EXIT_FAILURE, "Image loading failed: %s", IMG_GetError());

    // Détection de l'angle de rotation
    double angle = detectRotationAngle(surface);
	printf("%f",angle);

    // Libérer la surface après détection de l'angle
    SDL_FreeSurface(surface);

    // Appel à display_image avec le chemin d'image
    display_image(image_path, angle);
}
