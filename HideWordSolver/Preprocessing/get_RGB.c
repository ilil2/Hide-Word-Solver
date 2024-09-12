#include "../Lib/lib.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <stdint.h>


void get_RGB(SDL_Surface *tmp, int pixel[][3])
{
	Uint32 *pixels = (Uint32 *)tmp->pixels;

    int width = tmp->w;
    int height = tmp->h;

    for (int y = 0; y < height; ++y)
	{
      	for (int x = 0; x < width; ++x)
		{
            int index = y * tmp->pitch / 4 + x;
            Uint32 pixel = pixels[index];

            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, tmp->format, &r, &g, &b, &a);
        }
    }

	for (size_t i = 0; (int)i < width*height; i++)
	{
		char hexa[7] = {};
		itox(pixels[i], hexa);

		int rgb[3] = {};
		xtoRGB(hexa, rgb);

		for (size_t j = 0; j < 3; j++)
		{
			pixel[i][j] = rgb[j];
		}
	}
}
