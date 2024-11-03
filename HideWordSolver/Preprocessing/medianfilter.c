#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>

#include "sort.h"

Uint32 median_mask(int x, int y, Uint32* pixels, int h)
{
	Uint32 neighbour_list[8];
        neighbour_list[0] = pixels[(x-1) * h + (y-1)];
        neighbour_list[1] = pixels[(x-1) * h + y];
        neighbour_list[2] = pixels[(x-1) * h + (y+1)];
        neighbour_list[3] = pixels[x * h + (y-1)];
        neighbour_list[4] = pixels[x * h + (y+1)];
        neighbour_list[5] = pixels[(x+1) * h + (y-1)];
        neighbour_list[6] = pixels[(x+1) * h + y];
        neighbour_list[7] = pixels[(x+1) * h + (y+1)];
        quickSort(neighbour_list,0,7);
        return neighbour_list[5];
}

void median_filter(SDL_Surface* surface)
{
	Uint32* pixels = surface->pixels;
	int w = surface->w;
	int h = surface->h;
	Uint32* cp_pixels = malloc(w*h*sizeof(Uint32));
	memcpy(cp_pixels, pixels, w*h*sizeof(Uint32));
	for (int i = 2; i < w -2; i++)
	{
		for (int j = 2; j < h -2; j++)
		{
			Uint32 res = median_mask(j, i, cp_pixels, w);
			pixels[j * w + i] = res;
		}
	}
	free(cp_pixels);
}
