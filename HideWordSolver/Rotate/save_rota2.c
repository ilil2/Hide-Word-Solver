#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "rotation.h"
#include <stdio.h>

double detectRotationAngle(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;

    // La variable pour accumuler les angles
    double total_angle = 0;
    int count = 0;

    // Appliquer la transformation de Hough pour détecter les lignes
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Uint32 pixel = *((Uint32*)image->pixels + y * width + x);
            // Vérifiez si le pixel est blanc dans l'image binaire (1 pour blanc, 0 pour noir)
            if (pixel == SDL_MapRGB(image->format, 255, 255, 255)) // Ajustez si nécessaire pour votre format
            {
                // Parcourez un voisinage autour du pixel blanc
                for (int dy = -1; dy <= 1; ++dy)
                {
                    for (int dx = -1; dx <= 1; ++dx)
                    {
                        if (dy != 0 || dx != 0)
                        {
                            // Vérifiez les pixels voisins
                            int nx = x + dx;
                            int ny = y + dy;

                            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                            {
                                Uint32 neighbor_pixel = *((Uint32*)image->pixels + ny * width + nx);
                                if (neighbor_pixel == SDL_MapRGB(image->format, 255, 255, 255))
                                {
                                    // Calculer l'angle de la ligne
                                    double angle = atan2(dy, dx) * (180.0 / M_PI);
                                    total_angle += angle;
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Calculer l'angle moyen
    double average_angle = count > 0 ? total_angle / count : 0;

    // Normaliser l'angle entre 0 et 360
    if (average_angle < 0)
        average_angle += 360;

    return 360 - average_angle; // Retourner l'angle pour redresser
}
