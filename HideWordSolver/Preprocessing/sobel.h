#ifndef SOBEL_H
#define SOBEL_H

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

Uint32 vertical_sobel_product(Uint32* submatrix,SDL_PixelFormat* format);

Uint32 horizontal_sobel_product(Uint32* submatrix, SDL_PixelFormat* format);

void vertical_sobel_filter(SDL_Surface* surface,Uint32* result);

void horizontal_sobel_filter(SDL_Surface* surface,Uint32* result);

void sobel(SDL_Surface* surface, Uint32* result);

#endif
