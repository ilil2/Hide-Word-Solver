#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <SDL2/SDL.h>

// sobel.c
Uint32 vertical_sobel_product(Uint32* submatrix, SDL_PixelFormat* format);
Uint32 horizontal_sobel_product(Uint32* submatrix, SDL_PixelFormat* format);
void vertical_sobel_filter(SDL_Surface* surface, Uint32* result);
void horizontal_sobel_filter(SDL_Surface* surface, Uint32* result);
void sobel(SDL_Surface* surface, Uint32* result);

// grayscale.c
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);
void surface_to_grayscale(SDL_Surface* surface);

// binarization.c
Uint32 pixel_to_black_or_white(Uint32 pixel_color, SDL_PixelFormat* format, Uint8 threshold);
void surface_to_black_and_white(SDL_Surface* surface, Uint8 threshold);
int otsus(int len, Uint32* pixels, SDL_PixelFormat* format);

#endif
