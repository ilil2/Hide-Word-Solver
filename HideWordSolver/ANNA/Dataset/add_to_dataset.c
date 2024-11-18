#include "main_dataset.h"
#include <unistd.h>

void add_to_dataset(const char *img, int i, char output, char test)
{
	FILE *file = fopen(img, "r");
	if (file != NULL)
	{
		fclose(file);

		// Convert image into .bmp file
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
				// Save image on csv file
				bmp_to_csv(tmp, i, output, test);
			}

			SDL_FreeSurface(tmp);
			SDL_Quit();
		}
	}
	else
	{
		printf("Error : The file does not exist\n");
	}
}
