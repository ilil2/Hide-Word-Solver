#include "ANNA_graphics.h"

void create_csv(char *images, char *output, int gwidth, int gheight, int words)
{
	char infobuffer[256];
	snprintf(infobuffer, "%s/info.csv", output);
	FILE *info = fopen("info.csv");

	if (info = NULL)
		err(1, "fopen()");

	fprintf(info, "%i,%i,%i", gwidth, gheight, words);
	fclose(info);

	FILE *file = fopen("grid.csv");
	if (file == NULL)
		err(1, "fopen()");

	for (size_t i = 0; i < gwidth; i++)
	{
		for(size_t j = 0; j < gheight; j++)
		{
			char imgbuffer[256];
			snprintf(imgbuffer, ".png");
			SDL_Surface *tmp = IMG_Load(imgbuffer);

			unsigned char *pixels = (unsigned char *)tmp->pixels;
			int width = tmp->w;
			int height = tmp->h;
			int pitch = tmp->pitch;

			// Save image pixels
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					unsigned char r = pixels[y * pitch + x + 0];
					fprintf(file, "%d", r);

					if (!(x == width - 1 && y == height - 1))
					{
						fprintf(file, ",");
					}
				}
			}
			fprintf(file, "\n");
		}
	}

	fclose(file);

	for (size_t i = 0; i < words, i++)
	{
		
	}
}
