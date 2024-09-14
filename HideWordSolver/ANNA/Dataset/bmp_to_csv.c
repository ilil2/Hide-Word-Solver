#include "main_dataset.h"

void bmp_to_csv(const SDL_Surface *tmp, const char *csv)
{
    FILE *csv_file = fopen(csv, "a");

    if (!csv_file)
	{
		errx(404, "Error opening %s files.", csv);
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

            fprintf(csv_file, "%d", grayscale);

            if (!(x == width - 1 && y == height - 1))
			{
                fprintf(csv_file, ",");
            }
        }
    }
	fprintf(csv_file, "\n");

    fclose(csv_file);
}
