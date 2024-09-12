#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <stdint.h>
#include "Preprocessing.h"

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		errx(400, "The number of argment is invalid.");
	}
	char command[256];
	snprintf(command, sizeof(command), "convert %s image.bmp", argv[1]);

	system(command);

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface *tmp = NULL; 
	SDL_Texture *texture = NULL;
	tmp = SDL_LoadBMP("image.bmp");

	texture = SDL_CreateTextureFromSurface(renderer, tmp);
	

	if(NULL == texture)
	{
    	fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
	}

	int width = tmp->w;
    int height = tmp->h;

	int pixel[width*height][3];

	get_RGB(tmp, pixel);

	SDL_FreeSurface(tmp);

	int quit = 0;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        // Efface l'écran et affiche la texture
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	execlp("rm", "rm", "image.bmp", NULL);

    return EXIT_SUCCESS;
}
