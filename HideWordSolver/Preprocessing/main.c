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
            errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_Surface * r = SDL_ConvertSurfaceFormat(temp,SDL_PIXELFORMAT_RGB888,0);
    if (r == NULL)
            errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_FreeSurface(temp);
    return r;
}

int main(int argc, char** argv)
{
	if(argc != 2)
		errx(1,"Usage : main [path_to_img]");
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(1,"%s",SDL_GetError());
	
	//Grayscale
	SDL_Surface* surface = load_image(argv[1]);
	surface_to_grayscale(surface);
	if(IMG_SavePNG(surface,"grayscaleIMG.png") != 0)
		errx(1,"%s",SDL_GetError());
	
	//Binarization
	SDL_PixelFormat* format = surface->format;
    	if (format == 0)
        	errx(EXIT_FAILURE, "%s", SDL_GetError());
    	int threshold = otsus(surface->w * surface->h, surface->pixels,format) - 4;
    	surface_to_black_and_white(surface,threshold);
    	if (IMG_SavePNG(surface,"blackandwhiteIMG.png")!=0)
        	errx(EXIT_FAILURE,"%s", SDL_GetError());
	
	//Median Filter
	median_filter(surface);
	if (IMG_SavePNG(surface,"medianfilterIMG.png") != 0)
		errx(EXIT_FAILURE,"%s", SDL_GetError());

	SDL_Quit();
	return 0;
}
