#include "../neural_network.h"
#include <unistd.h>

void add_to_dataset(const char *img, const char *csv)
{
	FILE *file = fopen(img, "r");
	if (file != NULL)
	{
		fclose(file);

		char command[256];
		snprintf(command, sizeof(command), "magick %s image.bmp", img);

		system(command);

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			errx(7, "Cannot initialise SDL: %s", SDL_GetError());
		}
		else
		{
			SDL_Surface *tmp = SDL_LoadBMP("image.bmp");

			if (!tmp)
			{
				SDL_Quit();
				printf("Cannot load BMP image: %s", SDL_GetError());
			}
			else
			{
				bmp_to_csv(tmp, csv);
			}

			SDL_FreeSurface(tmp);
			SDL_Quit();
		}
	}
	else
	{
		printf("The file does not exist\n");
	}
}
