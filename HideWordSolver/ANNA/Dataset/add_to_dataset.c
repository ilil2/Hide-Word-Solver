#include "../neural_network.h"
#include <unistd.h>

void add_to_dataset(const char *img, const char *csv)
{   
	char command[256];
	snprintf(command, sizeof(command), "convert %s image.bmp", img);

	system(command);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		errx(6, "Cannot initialise SDL: %s", SDL_GetError());
	}

	SDL_Surface *tmp = SDL_LoadBMP("image.bmp");

	if (!tmp)
	{
		SDL_Quit();
		errx(8, "Cannot load BMP image: %s", SDL_GetError());
	}

	bmp_to_csv(tmp, csv);

	SDL_FreeSurface(tmp);
    SDL_Quit();

	execlp("rm", "rm", "image.bmp", NULL);
}
