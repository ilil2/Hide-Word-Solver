#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "sort.h"

Uint32* median_mask(int x, int y, SDL_Surface* surface);

void median_filter(SDL_Surface* surface);

#endif
