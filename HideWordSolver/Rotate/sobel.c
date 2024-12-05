#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

Uint32 vertical_sobel_product(Uint32* submatrix, SDL_PixelFormat* format) {
    int vertical_convolution_matrix[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int result = 0;
    Uint8 r, g, b;

    for (int i = 0; i < 9; i++) {
        SDL_GetRGB(submatrix[i], format, &r, &g, &b);
        result += vertical_convolution_matrix[i] * r;
    }

    result = result < 0 ? 0 : (result > 255 ? 255 : result);
    return SDL_MapRGB(format, result, result, result);
}

Uint32 horizontal_sobel_product(Uint32* submatrix, SDL_PixelFormat* format) {
    int horizontal_convolution_matrix[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int result = 0;
    Uint8 r, g, b;

    for (int i = 0; i < 9; i++) {
        SDL_GetRGB(submatrix[i], format, &r, &g, &b);
        result += horizontal_convolution_matrix[i] * r;
    }

    result = result < 0 ? 0 : (result > 255 ? 255 : result);
    return SDL_MapRGB(format, result, result, result);
}

void vertical_sobel_filter(SDL_Surface* surface, Uint32* result) {
    Uint32* pixels = (Uint32*)surface->pixels;
    int width = surface->w;
    int height = surface->h;
    SDL_PixelFormat* format = surface->format;

    SDL_LockSurface(surface);

    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            Uint32 submatrix[] = {
                pixels[(j - 1) * width + (i - 1)],
                pixels[(j - 1) * width + i],
                pixels[(j - 1) * width + (i + 1)],
                pixels[j * width + (i - 1)],
                pixels[j * width + i],
                pixels[j * width + (i + 1)],
                pixels[(j + 1) * width + (i - 1)],
                pixels[(j + 1) * width + i],
                pixels[(j + 1) * width + (i + 1)]
            };

            result[(j - 1) * (width - 2) + (i - 1)] = vertical_sobel_product(submatrix, format);
        }
    }

    SDL_UnlockSurface(surface);
}

void horizontal_sobel_filter(SDL_Surface* surface, Uint32* result) {
    Uint32* pixels = (Uint32*)surface->pixels;
    int width = surface->w;
    int height = surface->h;
    SDL_PixelFormat* format = surface->format;

    SDL_LockSurface(surface);

    for (int j = 1; j < height - 1; j++) {
        for (int i = 1; i < width - 1; i++) {
            Uint32 submatrix[] = {
                pixels[(j - 1) * width + (i - 1)],
                pixels[(j - 1) * width + i],
                pixels[(j - 1) * width + (i + 1)],
                pixels[j * width + (i - 1)],
                pixels[j * width + i],
                pixels[j * width + (i + 1)],
                pixels[(j + 1) * width + (i - 1)],
                pixels[(j + 1) * width + i],
                pixels[(j + 1) * width + (i + 1)]
            };

            result[(j - 1) * (width - 2) + (i - 1)] = horizontal_sobel_product(submatrix, format);
        }
    }

    SDL_UnlockSurface(surface);
}

void sobel(SDL_Surface* surface, Uint32* result) {
    int width = surface->w;
    int height = surface->h;
    int len = (width - 2) * (height - 2); 
    

    Uint32* vertical_matrix = malloc(len * sizeof(Uint32));
    Uint32* horizontal_matrix = malloc(len * sizeof(Uint32));

    vertical_sobel_filter(surface, vertical_matrix);
    horizontal_sobel_filter(surface, horizontal_matrix);

    SDL_PixelFormat* format = surface->format;
    Uint8 rh, gh, bh, rv, gv, bv;

    for (int j = 0; j < height - 2; j++) {
        for (int i = 0; i < width - 2; i++) {
            SDL_GetRGB(horizontal_matrix[j * (width - 2) + i], format, &rh, &gh, &bh);
            SDL_GetRGB(vertical_matrix[j * (width - 2) + i], format, &rv, &gv, &bv);

            Uint8 color = sqrt(rh * rh + rv * rv);
            result[j * (width - 2) + i] = SDL_MapRGB(format, color, color, color);
        }
    }

    free(vertical_matrix);
    free(horizontal_matrix);
}
