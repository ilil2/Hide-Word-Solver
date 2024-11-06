#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_PI 3.14159265358979323846

// Fonction pour convertir une SDL_Surface en niveaux de gris
void convertToGrayscale(SDL_Surface* surface) {
    Uint32* pixels = (Uint32*)surface->pixels;
    int width = surface->w;
    int height = surface->h;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint32 pixel = pixels[y * width + x];

            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            // Conversion en niveaux de gris
            Uint8 gray = (Uint8)(0.299 * r + 0.587 * g + 0.114 * b);
            pixels[y * width + x] = SDL_MapRGB(surface->format, gray, gray, gray);
        }
    }
}

// Calcul du noyau de passe-bas circulaire X (sans fonction Bessel)
void circularLowpassKernelX(double omega_c, int N, double* kernel) {
    int mid = (N - 1) / 2;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            double dist_x = (x - mid) / ((N - 1) / 2 + 1);
            double dist_y = (y - mid) / ((N - 1) / 2 + 1);
            double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

            // Utilisation d'une approche simplifiée sans la fonction Bessel (juste une forme de filtre radiale)
            kernel[y * N + x] = omega_c * omega_c * dist_x * exp(-dist * dist / 2.0) / (2 * M_PI * dist);
        }
    }
}

// Calcul du noyau de passe-bas circulaire Y (sans fonction Bessel)
void circularLowpassKernelY(double omega_c, int N, double* kernel) {
    int mid = (N - 1) / 2;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            double dist_x = (x - mid) / ((N - 1) / 2 + 1);
            double dist_y = (y - mid) / ((N - 1) / 2 + 1);
            double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

            // Utilisation d'une approche simplifiée sans la fonction Bessel (juste une forme de filtre radiale)
            kernel[y * N + x] = omega_c * omega_c * dist_y * exp(-dist * dist / 2.0) / (2 * M_PI * dist);
        }
    }
}

// Fonction principale de détection de l'angle de rotation
double detectRotationAngle(SDL_Surface* surface, double omega_c, int N) {
    int width = surface->w;
    int height = surface->h;

    // Convertir l'image en niveaux de gris
    convertToGrayscale(surface);

    // Créer les noyaux circulaires
    double* kernelX = (double*)malloc(N * N * sizeof(double));
    double* kernelY = (double*)malloc(N * N * sizeof(double));
    circularLowpassKernelX(omega_c, N, kernelX);
    circularLowpassKernelY(omega_c, N, kernelY);

    // Étape 1 : Appliquer les noyaux à l'image
    double sumX = 0.0, sumY = 0.0;

    for (int y = 0; y < height - N; y++) {
        for (int x = 0; x < width - N; x++) {
            // Appliquer les noyaux à la région de l'image
            double sumKernelX = 0.0, sumKernelY = 0.0;

            for (int ky = 0; ky < N; ky++) {
                for (int kx = 0; kx < N; kx++) {
                    int pixel = ((Uint32*)surface->pixels)[(y + ky) * width + (x + kx)] & 0xFF; // Niveaux de gris
                    sumKernelX += pixel * kernelX[ky * N + kx];
                    sumKernelY += pixel * kernelY[ky * N + kx];
                }
            }

            // Accumuler les valeurs
            sumX += sumKernelX;
            sumY += sumKernelY;
        }
    }

    // Étape 2 : Calculer l'angle de rotation
    double angle = atan2(sumY, sumX) * 180.0 / M_PI;  // Convertir de radians en degrés

    free(kernelX);
    free(kernelY);

    return angle;
}

