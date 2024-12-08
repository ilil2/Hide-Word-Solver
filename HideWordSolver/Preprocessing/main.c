#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "grayscale.h"
#include "binarization.h"
#include "medianfilter.h"
#include "sobel.h"

SDL_Surface* load_image(const char* path)
{
    SDL_Surface * temp = IMG_Load(path);
    if (temp == NULL)
	{
		SDL_FreeSurface(temp);
		SDL_Quit();
		IMG_Quit();
    	errx(EXIT_FAILURE, "%s", SDL_GetError());
    }
	SDL_Surface * r = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGB888,0);
    if (r == NULL)
	{
		SDL_FreeSurface(temp);
		SDL_Quit();
		IMG_Quit();
		errx(EXIT_FAILURE, "%s", SDL_GetError());
    }
	SDL_FreeSurface(temp);
    return r;
}

int main(int argc, char** argv)
{
	IMG_Init(IMG_INIT_PNG);

	if(argc != 2)
	{
		IMG_Quit();
		errx(1,"Usage : main [path_to_img]");
	}

	if(SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	{
		IMG_Quit();
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		errx(1,"%s",SDL_GetError());
	}

	SDL_Surface* surface = load_image(argv[1]);
	
	//Grayscale
	surface_to_grayscale(surface);

	if(IMG_SavePNG(surface,"grayscaleIMG.png") != 0)
	{
		SDL_FreeSurface(surface);
		SDL_Quit();
		IMG_Quit();
		errx(1,"%s",SDL_GetError());
	}

	//Binarization
	SDL_PixelFormat* format = surface->format;

	if (format == 0)
	{
		SDL_FreeSurface(surface);
		SDL_Quit();
		IMG_Quit();
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	}

	int threshold = otsus(surface->w * surface->h, surface->pixels,format);
	surface_to_black_and_white(surface,threshold);

	if (IMG_SavePNG(surface,"blackandwhiteIMG.png")!=0)
	{
		SDL_FreeSurface(surface);
		SDL_Quit();
		IMG_Quit();
		errx(EXIT_FAILURE,"%s", SDL_GetError());
	}

	//Sobel pre median filter
	int len = surface->w * surface->h;
	Uint32* pixels = malloc(4*len);
	
	//Median Filter
	median_filter(surface);

	if (IMG_SavePNG(surface,"medianfilterIMG.png") != 0)
	{
		SDL_FreeSurface(surface);
		SDL_Quit();
		IMG_Quit();
		errx(EXIT_FAILURE,"%s", SDL_GetError());
	}

	//Sobel post median filter
	sobel(surface,pixels);

    surface->pixels = pixels;

	if (IMG_SavePNG(surface,"sobel2IMG.png") != 0)
	{
		SDL_FreeSurface(surface);
		SDL_Quit();
		IMG_Quit();
		errx(EXIT_FAILURE,"%s", SDL_GetError());
	}


	IMG_Quit();
	//SDL_FreeSurface(surface);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	return 0;
}
