#include "main_dataset.h"

void bmp_to_csv(const SDL_Surface *tmp, int i, char output, char test)
{
    char ibuffer[100];
    char obuffer[100];
    if (test)
    {
        sprintf(ibuffer, "Train1/tx.csv");
        sprintf(obuffer, "Train1/ty.csv");
    }
    else
    {
        sprintf(ibuffer, "Train1/x%i.csv", i);
        sprintf(obuffer, "Train1/y%i.csv", i);
    }
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

    // Save image pixels
    for (int y = 0; y < height; y++)
	{
        for (int x = 0; x < width; x++)
		{
            unsigned char r = pixels[y * pitch + x + 0];
            unsigned char g = pixels[y * pitch + x + 1];
            unsigned char b = pixels[y * pitch + x + 2];

            // Apply grayscale
            unsigned char grayscale =
                (unsigned char)(0.3 * r + 0.59 * g + 0.11 * b);

            fprintf(input_file, "%d", grayscale);

            if (!(x == width - 1 && y == height - 1))
			{
                fprintf(input_file, ",");
            }
        }
    }
	fprintf(input_file, "\n");

    // Save output
    fprintf(output_file, "%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,"
        "%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,"
        "%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c\n",
        (output == 'A') + '0', (output == 'B') + '0', (output == 'C') + '0',
        (output == 'D') + '0', (output == 'E') + '0', (output == 'F') + '0',
        (output == 'G') + '0', (output == 'H') + '0', (output == 'I') + '0',
        (output == 'J') + '0', (output == 'K') + '0', (output == 'L') + '0',
        (output == 'M') + '0', (output == 'N') + '0', (output == 'O') + '0',
        (output == 'P') + '0', (output == 'Q') + '0', (output == 'R') + '0',
        (output == 'S') + '0', (output == 'T') + '0', (output == 'U') + '0',
        (output == 'V') + '0', (output == 'W') + '0', (output == 'X') + '0',
        (output == 'Y') + '0', (output == 'Z') + '0', (output == 'a') + '0', 
        (output == 'b') + '0', (output == 'c') + '0', (output == 'd') + '0',
        (output == 'e') + '0', (output == 'f') + '0', (output == 'g') + '0',
        (output == 'h') + '0', (output == 'i') + '0', (output == 'j') + '0',
        (output == 'k') + '0', (output == 'l') + '0', (output == 'm') + '0',
        (output == 'n') + '0', (output == 'o') + '0', (output == 'p') + '0',
        (output == 'q') + '0', (output == 'r') + '0', (output == 's') + '0',
        (output == 't') + '0', (output == 'u') + '0', (output == 'v') + '0',
        (output == 'w') + '0', (output == 'x') + '0', (output == 'y') + '0',
        (output == 'z') + '0');
    
    fclose(input_file);
    fclose(output_file);
}
