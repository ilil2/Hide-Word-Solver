#ifndef BLACKANDWHITE_H
#define BLACKANDWHITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int otsus(int len,Uint32 * pixels, SDL_PixelFormat* format);

Uint32 pixel_to_black_or_white(Uint32 pixel_color, SDL_PixelFormat* format,
		Uint8 threshold);

void surface_to_black_and_white(SDL_Surface* surface,Uint8 threshold);

#endif

