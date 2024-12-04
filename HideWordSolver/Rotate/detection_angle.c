#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rotation.h"

// Fonction de détection de l'angle de rotation avec la transformée de Hough
double detectRotationAngle(SDL_Surface* surface) 
{
    int width = surface->w;
    int height = surface->h;

    // Créer un tableau d'accumulation pour l'espace de Hough
    int diag_len = (int)sqrt(width * width + height * height);
    int* houghSpace = (int*)calloc((2 * diag_len) * 180, sizeof(int));

    if (!houghSpace) {
        fprintf(stderr, "Erreur d'allocation mémoire pour houghSpace\n");
        return 0.0;
    }

    // Appliquer le filtre Sobel pour obtenir les bords de l'image
    Uint32* sobelResult = (Uint32*)malloc(sizeof(Uint32) * width * height);
    if (!sobelResult) {
        fprintf(stderr, "Erreur d'allocation mémoire pour sobelResult\n");
        free(houghSpace);
        return 0.0;
    }

    sobel(surface, sobelResult);  // Utilisation de la fonction Sobel pour obtenir les bords

    // Parcourir chaque pixel de l'image filtrée par Sobel
    SDL_PixelFormat* format = surface->format;
    int countBords = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint32 pixel = sobelResult[y * width + x];
            Uint8 r, g, b;
            SDL_GetRGB(pixel, format, &r, &g, &b);

            // Si le pixel est un bord (déterminé par l'intensité)
            if (r < 50) {  // Seulement les pixels très sombres sont considérés comme bords
                countBords++;

                for (int theta = 0; theta < 180; theta++) {
                    double theta_rad = theta * M_PI / 180.0;
                    int r_val = (int)(x * cos(theta_rad) + y * sin(theta_rad));

                    int houghIndex = (r_val + diag_len) * 180 + theta;
                    if (houghIndex >= 0 && houghIndex < (2 * diag_len) * 180) {
                        houghSpace[houghIndex]++;
                    }
                }
            }
        }
    }

    printf("Nombre de pixels considérés comme bords: %d\n", countBords);

    // Chercher l'angle avec le maximum d'accumulation
    int maxAcc = 0;
    int bestTheta = 0;

    for (int theta = 0; theta < 180; theta++) {
        for (int r = 0; r < 2 * diag_len; r++) {
            int houghIndex = r * 180 + theta;
            if (houghSpace[houghIndex] > maxAcc) {
                maxAcc = houghSpace[houghIndex];
                bestTheta = theta;
            }
        }
    }

    printf("Accumulation maximale: %d pour theta = %d\n", maxAcc, bestTheta);

    free(houghSpace);
    free(sobelResult);

    // Retourner l'angle détecté en degrés
    return (double)bestTheta;
}
