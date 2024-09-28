#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

SDL_Window *create_window(char *title,
		unsigned int width,
		unsigned int height)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		return NULL;
	SDL_Window* window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	return window;
}


SDL_Renderer *create_renderer(SDL_Window *window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

	return renderer;
}


SDL_Texture* loadImage(const char* file, SDL_Renderer* renderer, int* width, int* height) 
{
    SDL_Surface* surface = IMG_Load(file);
    if (!surface) {
        fprintf(stderr, "Error loading image %s: %s\n", file, IMG_GetError());
        SDL_Quit();
        exit(1);    
}

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_Quit();
        exit(1);
    }

    *width = surface->w;
    *height = surface->h;

    SDL_FreeSurface(surface);
    return texture;
}


void displayImage(SDL_Renderer* renderer, SDL_Texture* texture, int imgWidth, int imgHeight, double angle) 
{
    SDL_RenderClear(renderer);

    SDL_Point center = { imgWidth / 2, imgHeight / 2 };

    SDL_Rect destRect = { 0, 0, imgWidth, imgHeight };

    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
}

int process_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			return 0;
	}
	return 1;
}

void cleanup(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window)
{
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void display_image(const char* image_file, float angle)
{
	
  
   
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
      
    }
	
    int imgWidth, imgHeight;

	SDL_Window *window = create_window("example", 800, 500);
	

    if (!window)
        errx(EXIT_FAILURE, "Failed to create SDL window: %s", SDL_GetError());
    
    SDL_Renderer *renderer = create_renderer(window);
    
    if (!renderer)
        errx(EXIT_FAILURE, "Failed to create SDL renderer: %s", SDL_GetError());

    SDL_Texture* texture = loadImage(image_file, renderer, &imgWidth, &imgHeight);

    SDL_SetWindowSize(window, imgWidth, imgHeight);

    int running = 1;
	
    while (running) {
        running = process_events();  
        displayImage(renderer, texture, imgWidth, imgHeight, angle);  
    }

    cleanup(texture, renderer, window);

 
}
