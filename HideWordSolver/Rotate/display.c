#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>
#include "rotation.h"

void display_image(const char* image_file, float angle) {
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int imgWidth, imgHeight;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "Failed to initialize SDL: %s", SDL_GetError());

    window = SDL_CreateWindow("example",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			800, 500, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
        errx(EXIT_FAILURE, "Failed to create SDL window: %s", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        errx(EXIT_FAILURE, "Failed to create SDL renderer: %s", SDL_GetError());

    SDL_Surface* surface = IMG_Load(image_file);
    if (!surface) {
        fprintf(stderr, "Error loading image %s: %s\n", image_file, IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_Quit();
        exit(1);
    }

    imgWidth = surface->w;
    imgHeight = surface->h;
    SDL_FreeSurface(surface);
    SDL_SetWindowSize(window, imgWidth, imgHeight);

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        SDL_RenderClear(renderer);
        SDL_Point center = { imgWidth / 2, imgHeight / 2 };
        SDL_Rect destRect = { 0, 0, imgWidth, imgHeight };
        SDL_RenderCopyEx(renderer, texture, NULL,
				&destRect, angle, &center, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
    }

    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
