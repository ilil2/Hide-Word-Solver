#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rotation.h"

double detectRotationAngle(SDL_Surface* surface) 
{
	//Def variable
    int imgWidth = surface->w;
    int imgHeight = surface->h;
    int diagonal = (int)sqrt(imgWidth * imgWidth + imgHeight * imgHeight);
    int rMax = 2 * diagonal;
    int thetaMax = 180;
    int* houghSpace = (int*)calloc(rMax * thetaMax, sizeof(int));

	//check erreur
    if (!houghSpace) {
        fprintf(stderr, "erreur malloc Hough");
        return 0.0;
    }

	//def pixels
    Uint32* imgPixels = (Uint32*)surface->pixels;

	//on parcours image
    for (int y = 0; y < imgHeight; y++) {
        for (int x = 0; x < imgWidth; x++) {
            Uint8 red;
            SDL_GetRGB(imgPixels[y * imgWidth + x], surface->format, &red, &red, &red);

			//check si pixel est blanc
            if (red == 255) {
                for (int theta = 0; theta < thetaMax; theta++) {
                    double thetaRad = theta * M_PI / 180.0;
                    int rValue = (int)(x * cos(thetaRad) + y * sin(thetaRad)) + diagonal;

                    if (rValue >= 0 && rValue < rMax) {
                        houghSpace[rValue * thetaMax + theta]++;
                    }
                }
            }
        }
    }

	//boucle qui cherche angle dominant (le fameux bestTheta)
    int maxVotes = 0;
    int bestTheta = 0;
    for (int r = 0; r < rMax; r++) {
        for (int theta = 0; theta < thetaMax; theta++) {
            if (houghSpace[r * thetaMax + theta] > maxVotes) {
                maxVotes = houghSpace[r * thetaMax + theta];
                bestTheta = theta;
            }
        }
    }

    free(houghSpace);

    double detectedAngle = (double)bestTheta;

	//check si il l'a met pas a l'envers ou de coté
	//(test bancale) 
    if (detectedAngle > 120) {
        detectedAngle += 180;
    } 
	else if (detectedAngle > 50) {
        detectedAngle -= 90;
    }

	//inverse l'angle car tourne dans le mauvais sens 
	//(sens inverse des aiguille d'une montre)
    return 360 - detectedAngle;
}
