#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SOBEL_THRESHOLD 100
#define HOUGH_THRESHOLD 100

// Détecter l'angle de rotation de l'image en utilisant Sobel et Hough
double detectRotationAngle(SDL_Surface* surface) {
    if (!surface) {
        fprintf(stderr, "Erreur: surface image non valide\n");
        return 0;
    }

    int width = surface->w;
    int height = surface->h;
    Uint32* pixels = (Uint32*)surface->pixels;

    // Étape 1 : Appliquer le filtre de Sobel pour détecter les bords
    double* sobelX = malloc(width * height * sizeof(double));
    double* sobelY = malloc(width * height * sizeof(double));
    memset(sobelX, 0, width * height * sizeof(double));
    memset(sobelY, 0, width * height * sizeof(double));

    // Matrices de convolution Sobel
    int sobelKernelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int sobelKernelY[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Appliquer le filtre de Sobel
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double gx = 0, gy = 0;

            // Calcul de Sobel X et Y sur une fenêtre 3x3
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    Uint32 pixel = pixels[(y + ky) * width + (x + kx)];
                    Uint8 r, g, b;
                    SDL_GetRGB(pixel, surface->format, &r, &g, &b);
                    int intensity = (r + g + b) / 3;  // Convertir en niveau de gris

                    gx += intensity * sobelKernelX[ky + 1][kx + 1];
                    gy += intensity * sobelKernelY[ky + 1][kx + 1];
                }
            }

            sobelX[y * width + x] = gx;
            sobelY[y * width + x] = gy;
        }
    }

    // Étape 2 : Calculer la magnitude des gradients et les directions
    double* gradientMagnitudes = malloc(width * height * sizeof(double));
    double* gradientAngles = malloc(width * height * sizeof(double));

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double gx = sobelX[y * width + x];
            double gy = sobelY[y * width + x];

            // Calcul de la magnitude et de l'angle du gradient
            gradientMagnitudes[y * width + x] = sqrt(gx * gx + gy * gy);
            gradientAngles[y * width + x] = atan2(gy, gx) * 180 / M_PI;  // Convertir en degrés
        }
    }

    // Libérer la mémoire des matrices Sobel
    free(sobelX);
    free(sobelY);

    // Étape 3 : Appliquer la transformation de Hough pour détecter les lignes
    int houghWidth = 180;  // 180 angles possibles (de -90 à 90)
    int houghHeight = sqrt(width * width + height * height);  // Taille de la diagonale de l'image
    int* houghSpace = calloc(houghWidth * houghHeight, sizeof(int));

    // Remplir l'accumulateur de Hough à partir des points détectés par Sobel
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            if (gradientMagnitudes[y * width + x] > SOBEL_THRESHOLD) {
                for (int theta = -90; theta < 90; ++theta) {
                    double thetaRad = theta * M_PI / 180;
                    int rho = (int)(x * cos(thetaRad) + y * sin(thetaRad));
                    if (rho >= 0 && rho < houghHeight) {
                        houghSpace[(theta + 90) * houghHeight + rho]++;
                    }
                }
            }
        }
    }

    // Trouver la valeur maximale dans l'espace de Hough (la ligne la plus probable)
    int maxVotes = 0;
    int bestTheta = 0;
    for (int theta = 0; theta < houghWidth; ++theta) {
        for (int rho = 0; rho < houghHeight; ++rho) {
            if (houghSpace[theta * houghHeight + rho] > maxVotes) {
                maxVotes = houghSpace[theta * houghHeight + rho];
                bestTheta = theta - 90;  // On retourne l'angle en degrés (-90 à 90)
            }
        }
    }

    // Libérer la mémoire de l'espace Hough et des gradients
    free(gradientMagnitudes);
    free(gradientAngles);
    free(houghSpace);

    // Retourner l'angle de la ligne principale détectée
    return (double)bestTheta;
}

// Fonction pour créer une fenêtre SDL
SDL_Window* createWindow(const char* title, int width, int height) {
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        exit(1);
    }
    return window;
}

// Fonction pour créer un renderer SDL
SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Erreur lors de la création du renderer: %s\n", SDL_GetError());
        exit(1);
    }
    return renderer;
}

// Fonction pour afficher l'image avec rotation
void displayImage(SDL_Renderer* renderer, SDL_Texture* texture, int width, int height, double angle) {
    SDL_RenderClear(renderer);
    SDL_Rect dstRect = {0, 0, width, height};
    SDL_RenderCopyEx(renderer, texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}

// Fonction pour gérer les événements SDL
int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;  // Quitter la boucle
        }
    }
    return 1;  // Continuer la boucle
}

// Fonction de nettoyage
void cleanup(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    const char* imageFile = argv[1];  // Chemin de l'image

    // Initialiser SDL et SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "Erreur SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Charger l'image et récupérer ses dimensions
    SDL_Surface* surface = IMG_Load(imageFile);
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image %s: %s\n", imageFile, IMG_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Détecter l'angle de rotation à partir de l'image
    double rotationAngle = detectRotationAngle(surface);  // Calcul automatique de l'angle

    // Créer une fenêtre et un renderer pour afficher l'image
    SDL_Window* window = createWindow("Image Rotation Automatique", surface->w, surface->h);
    SDL_Renderer* renderer = createRenderer(window);
    
    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // Libérer la surface après avoir créé la texture

    // Boucle principale pour afficher l'image et gérer les événements
    int running = 1;
    while (running) {
        running = handleEvents();  // Gérer les événements
        displayImage(renderer, texture, surface->w, surface->h, rotationAngle);  // Afficher l'image avec rotation
    }

    // Nettoyer les ressources et quitter
    cleanup(texture, renderer, window);

    return 0;
}
