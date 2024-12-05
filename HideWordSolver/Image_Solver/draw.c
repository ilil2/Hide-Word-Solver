#include "draw.h"

int draw_line(char *path, int x1, int y1, int x2, int y2)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    // load input image
    SDL_Surface* image = IMG_Load(path);
    if (!image) {
        printf("Image NULL\n");
        return -1;
    }

    // create target surface
    SDL_Surface *output_surface = SDL_CreateRGBSurface(0,
            image->w, image->h, 32,
            0, 0, 0, 0);

    // create software renderer that renders to target surface
    SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(output_surface);

    // create texture from input surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	int scale = 10;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	SDL_RenderSetScale(renderer, scale, scale);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderDrawLine(renderer, x1/scale, y1/scale, x2/scale, y2/scale);
    SDL_RenderPresent(renderer);

	IMG_SavePNG(output_surface, "result.png");

	// Destroy and free
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_FreeSurface(output_surface);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();

	return 0;
}
