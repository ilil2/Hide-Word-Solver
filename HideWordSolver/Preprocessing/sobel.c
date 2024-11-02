#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

Uint32 vertical_sobel_product(Uint32* submatrix,SDL_PixelFormat* format)
{
	Uint8 vertical_convolution_matrix[] ={-1,0,1,-2,0,2,-1,0,1};
	Uint8 result = 0;
	
	Uint8 r,g,b;
	
	
	for (int i =0; i < 9;i++)
	{
		SDL_GetRGB(submatrix[i], format, &r, &g, &b);
		
		result += vertical_convolution_matrix[i] * r;
	}

	if (result > 0) result = 255;
	
	return SDL_MapRGB(format, result, result, result);
}

Uint32 horizontal_sobel_product(Uint32* submatrix, SDL_PixelFormat* format)
{
	Uint8 horizontal_convolution_matrix[] ={-1,-2,-1,0,0,0,1,2,1};
	Uint8 result = 0;
	Uint8 r,g,b;
	for (int i =0; i < 9;i++)
	{
		SDL_GetRGB(submatrix[i], format, &r, &g, &b);
		result += horizontal_convolution_matrix[i] * r;
	}

	if (result > 0) result = 255;
	return SDL_MapRGB(format, result, result, result);
}

void vertical_sobel_filter(SDL_Surface* surface,Uint32* result)
{
    Uint32* pixels = surface->pixels;
    
    if (pixels == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
        
    
        
    int width = surface->w;
    int height = surface->h;

    
    SDL_PixelFormat* format = surface->format;
    if (format == 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
	
    if (SDL_LockSurface(surface) < 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
     
    for (int i =1; i<width-1;i++)
    {
        for (int j =1; j<height-1;j++)
        {
		Uint32 submatrix[] = 
		{ 
			pixels[(j-1)*width + (i-1)], 
			pixels[(j-1)*width + (i)],
			pixels[(j-1)*width + (i+1)],
			pixels[(j)*width + (i-1)],
			pixels[(j)*width + (i)], 
			pixels[(j)*width + (i+1)],
			pixels[(j+1)*width + (i-1)],
			pixels[(j+1)*width + (i)],
			pixels[(j+1)*width + (i+1)] 
		};
		result[j*width+i] = vertical_sobel_product(submatrix,format);
	}
    }
    SDL_UnlockSurface(surface);
}

void horizontal_sobel_filter(SDL_Surface* surface,Uint32* result)
{
    Uint32* pixels = surface->pixels;
    
    if (pixels == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
        
    int width = surface->w;
    int height = surface->h;
    
    SDL_PixelFormat* format = surface->format;
    if (format == 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
	
    if (SDL_LockSurface(surface) < 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
     
    for (int i =1; i<width-1;i++)
    {
        for (int j =1; j<height-1;j++)
        {
				Uint32 submatrix[] = 
				{ 
					pixels[(j-1)*width + (i-1)], 
					pixels[(j-1)*width + (i)],
					pixels[(j-1)*width + (i+1)],
					pixels[(j)*width + (i-1)],
					pixels[(j)*width + (i)], 
					pixels[(j)*width + (i+1)],
					pixels[(j+1)*width + (i-1)],
					pixels[(j+1)*width + (i)],
					pixels[(j+1)*width + (i+1)] 
				};
				result[j*width+i] = horizontal_sobel_product(submatrix,format);
	}
    }
    SDL_UnlockSurface(surface);
}

void sobel(SDL_Surface* surface, Uint32* result)
{
	int len = surface->w * surface->h;
    	if (len == 0)
        	errx(EXIT_FAILURE, "%s", SDL_GetError());
        
    	Uint32* vertical_matrix = malloc(4*len);
	Uint32* horizontal_matrix = malloc(4*len);
	
	vertical_sobel_filter(surface, vertical_matrix);
	horizontal_sobel_filter(surface,horizontal_matrix);

    
    	SDL_PixelFormat* format = surface->format;
    
    	if (format == 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	Uint8 rh, gh, bh, rv,gv,bv;
	for (int i =0; i<len;i++)
	{
        
		SDL_GetRGB(horizontal_matrix[i], format, &rh, &gh, &bh);
		SDL_GetRGB(vertical_matrix[i], format, &rv, &gv, &bv);
		Uint8 color = rh;
		result[i] = SDL_MapRGB(format, color, color, color);
	}
}
