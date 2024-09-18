#include "main_dataset.h"

void bmp_to_csv(const SDL_Surface *tmp, int i, char output)
{
    char ibuffer[100];
    char obuffer[100];
    sprintf(ibuffer, "Train/x%i.csv", i);
    sprintf(obuffer, "Train/y%i.csv", i);
    FILE *input_file = fopen(ibuffer, "a");
    FILE *output_file = fopen(obuffer, "a");

    if (!input_file)
	{
		errx(404, "Error opening %s files.", ibuffer);
    }

    if (!output_file)
    {
		errx(404, "Error opening %s files.", obuffer);
    }

    unsigned char *pixels = (unsigned char *)tmp->pixels;
    int width = tmp->w;
    int height = tmp->h;
    int pitch = tmp->pitch;

    for (int y = 0; y < height; y++)
	{
        for (int x = 0; x < width; x++)
		{
            unsigned char r = pixels[y * pitch + x + 0];
            unsigned char g = pixels[y * pitch + x + 1];
            unsigned char b = pixels[y * pitch + x + 2];

            unsigned char grayscale = (unsigned char)((r + g + b) / 3);

            fprintf(input_file, "%d", grayscale);

            if (!(x == width - 1 && y == height - 1))
			{
                fprintf(input_file, ",");
            }
        }
    }
	fprintf(input_file, "\n");

    fprintf(output_file, "%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c\n",
        (output == 'A') + '0', (output == 'B') + '0', (output == 'C') + '0',
        (output == 'D') + '0', (output == 'E') + '0', (output == 'F') + '0',
        (output == 'G') + '0', (output == 'H') + '0', (output == 'I') + '0',
        (output == 'J') + '0', (output == 'K') + '0', (output == 'L') + '0',
        (output == 'M') + '0', (output == 'N') + '0', (output == 'O') + '0',
        (output == 'P') + '0', (output == 'Q') + '0', (output == 'R') + '0',
        (output == 'S') + '0', (output == 'T') + '0', (output == 'U') + '0',
        (output == 'V') + '0', (output == 'W') + '0', (output == 'X') + '0',
        (output == 'Y') + '0', (output == 'Z') + '0');
    
    fclose(input_file);
    fclose(output_file);
}
