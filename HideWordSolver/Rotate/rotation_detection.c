#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

// Fonction de détection de l'angle de rotation avec la transformée de Hough
double detectRotationAngle(SDL_Surface* surface) 
{
    int width = surface->w;
    int height = surface->h;

    // Créer un tableau d'accumulation pour l'espace de Hough
    int diag_len = (int)sqrt(width * width + height * height);
    int* houghSpace = (int*)calloc(diag_len * 180, sizeof(int));

    // Convertir l'image en niveaux de gris (si pas déjà fait)
    Uint32* pixels = (Uint32*)surface->pixels;

    // Parcourir chaque pixel de l'image
    for (int y = 0; y < height; y++) 
	{
        for (int x = 0; x < width; x++) 
		{
            Uint32 pixel = pixels[y * width + x];
            Uint8 gray;
            SDL_GetRGB(pixel, surface->format, &gray, &gray, &gray);

            // Si le pixel est un bord (noir dans l'image en niveaux de gris)
            if (gray < 128) {  // Seulement les pixels "bord" (sombres)
                // Pour chaque pixel de bord, calculer les valeurs de Hough
                for (int theta = 0; theta < 180; theta++) {
                    double theta_rad = theta * M_PI / 180.0;
                    int r = (int)(x * cos(theta_rad) + y * sin(theta_rad));

                    // Indexer dans l'espace de Hough
                    int houghIndex = (r + diag_len / 2) * 180 + theta;
                    houghSpace[houghIndex]++;
                }
            }
        }
    }

    // Chercher l'angle avec le maximum d'accumulation
    int maxAcc = 0;
    int bestTheta = 0;
    for (int theta = 0; theta < 180; theta++) {
        for (int r = -diag_len / 2; r < diag_len / 2; r++) {
            int houghIndex = (r + diag_len / 2) * 180 + theta;
            if (houghSpace[houghIndex] > maxAcc) {
                maxAcc = houghSpace[houghIndex];
                bestTheta = theta;
            }
        }
    }

    free(houghSpace);

    // L'angle de la ligne détectée en degrés
    return (double)bestTheta;
}
