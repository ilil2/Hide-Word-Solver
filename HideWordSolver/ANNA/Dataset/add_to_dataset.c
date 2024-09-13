#include "../neural_network.h"
#include <unistd.h>

int add_to_dataset(const char *img, const char *csv)
{   
	char command[256];
	snprintf(command, sizeof(command), "magick %s image.bmp", img);

	system(command);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Cannot initialise SDL: %s", SDL_GetError());
		fflush(stdout);
		return 1;
	}

	SDL_Surface *tmp = SDL_LoadBMP("image.bmp");

	if (!tmp)
	{
		SDL_Quit();
		printf("Cannot load BMP image: %s", SDL_GetError());
		fflush(stdout);
		return 1;
	}

	bmp_to_csv(tmp, csv);

	SDL_FreeSurface(tmp);
    SDL_Quit();

	return 0;
}
