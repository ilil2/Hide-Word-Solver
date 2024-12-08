#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>


//Otsu's algorithm
//Adaptable threshold

int otsus(int len, Uint32 * pixels, SDL_PixelFormat* format)
{
        unsigned char* histogram = calloc(256,sizeof(unsigned char));
		if (histogram == NULL)
		{
			err(EXIT_FAILURE,"histogram:");
		}
        Uint8 r, g, b;
        for (int i=0;i<len;i++)
        {
                SDL_GetRGB(pixels[i], format, &r, &g, &b);
                histogram[r]+=1;
        }

        int top = 256;
        int sumB =0;
        int wB=0;
        long maximum = 0.0;
        int sum1 =0;
        int wF;
        int mF;
        int val;
        int level =0;

        for (int j =0; j<top;j++)
        {
                sum1+= histogram[j] *j;
        }

        for (int k =1;k<top;k++)
        {
                wF =len -wB;
                if (wB>0 && wF>0)
                {
                        mF = (sum1-sumB)/wF;
                        val = wB * wF * ((sumB / wB) - mF) * ((sumB / wB) - mF);
                        if ( val >= maximum )
                        {
                                level = k;
                                maximum = val;
                        }
                }
                wB+= histogram[k];
                sumB = sumB + (k-1) * histogram[k];
        }

		free(histogram);
		if (level == 255 || level == 0)
		{
			level = 127;
		}
        return level;

}
/*
int otsus(int len, Uint32 * pixels, SDL_PixelFormat* format)
{

	//Intensity histogram
	unsigned char* histogram = calloc(256,sizeof(unsigned char));
	if (histogram == NULL)
	{
		err(EXIT_FAILURE,"histogram:");
	}

	Uint8 r, g, b;
	for (int i=0;i<len;i++)
	{
			SDL_GetRGB(pixels[i], format, &r, &g, &b);
			histogram[r]+=1;
	}
	
	//Finding threshold that maximises the variance
	float* cdf = calloc(256, sizeof(float));
	if (cdf == NULL)
	{
		err(EXIT_FAILURE, "cdf:");
	}

	
	int threshold = 0;
	float length = (float)len;
	float maximum = 0.0;
	float var;
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			cdf[i] += (float)histogram[j];
		}
		cdf[i] /= length;

		//Probabilities of foreground and background
		float p0 = cdf[i];
		float p1 = 1 - cdf[i];
		
		float m0;
		for (int j = 0; j < i; j++)
		{
			m0 += histogram[j] * j;
		}
		m0 /= p0 * length;

		float m1;
		for (int j = i; j < 256; j++)
		{
			m1 += histogram[j] * j;
		}
		m1 /= p1 * length;

		var = p0 * p1 * ((m0 - m1) * (m0 - m1));
		printf("var: %f\n", var);
		if (var > maximum)
		{
			threshold = i;
			maximum = var;
		}
	}

	free(cdf);
	free(histogram);
	return threshold;

}*/
// Converts a colored pixel into blakc or white pixel depending on its clarity.
//
// pixel_color: Color of the pixel to convert in the RGB format.
// format: Format of the pixel used by the surface.

Uint32 pixel_to_black_or_white(Uint32 pixel_color, SDL_PixelFormat* format,
	Uint8 threshold)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);

    if (r>threshold)
    {
            return SDL_MapRGB(format, 0, 0, 0);
    }
    else
    {
            return SDL_MapRGB(format, 255, 255, 255);
    }
}

void surface_to_black_and_white(SDL_Surface* surface,Uint8 threshold)
{
    Uint32* pixels = surface->pixels;
    if (pixels == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    int len = surface->w * surface->h;
    if (len == 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_PixelFormat* format = surface->format;
    if (format == 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    if (SDL_LockSurface(surface) < 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    for (int i =0; i<len;i++)
        pixels[i] = pixel_to_black_or_white(pixels[i],format,threshold);
    SDL_UnlockSurface(surface);
}
