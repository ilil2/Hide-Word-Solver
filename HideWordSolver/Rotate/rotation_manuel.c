#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction pour initialiser SDL et créer une fenêtre
SDL_Window* createWindow(const char* title, int width, int height) {
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        exit(1); // Quitter en cas d'erreur
    }
    return window;
}

// Fonction pour créer un renderer
SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1); // Quitter en cas d'erreur
    }
    return renderer;
}

// Fonction pour charger l'image et la transformer en texture
SDL_Texture* loadImage(const char* file, SDL_Renderer* renderer, int* width, int* height) {
    SDL_Surface* surface = IMG_Load(file);  // Charger l'image
    if (!surface) {
        fprintf(stderr, "Erreur lors du chargement de l'image %s: %s\n", file, IMG_GetError());
        SDL_Quit();
        exit(1); // Quitter en cas d'erreur
    }

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Erreur lors de la création de la texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_Quit();
        exit(1); // Quitter en cas d'erreur
    }

    // Obtenir la largeur et la hauteur de l'image
    *width = surface->w;
    *height = surface->h;

    SDL_FreeSurface(surface);  // Libérer la surface après création de la texture
    return texture;
}

// Fonction pour afficher l'image avec rotation
void displayImage(SDL_Renderer* renderer, SDL_Texture* texture, int imgWidth, int imgHeight, double angle) {
    // Effacer l'écran
    SDL_RenderClear(renderer);

    // Définir le centre de rotation au centre de l'image
    SDL_Point center = { imgWidth / 2, imgHeight / 2 };

    // Définir la zone de rendu dans la fenêtre
    SDL_Rect destRect = { 0, 0, imgWidth, imgHeight };

    // Appliquer la rotation et afficher l'image
    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);

    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer);
}

// Fonction pour gérer les événements (fermeture de la fenêtre)
int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;  // Quitter l'application
        }
    }
    return 1;  // Continuer à exécuter
}

// Fonction pour gérer la fermeture et nettoyer les ressources
void cleanup(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window) {
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <image_file> <angle_de_rotation>\n", argv[0]);
        return 1;
    }

    const char* imageFile = argv[1];  // Chemin de l'image
    double angle = atof(argv[2]);     // Angle de rotation

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

    int imgWidth, imgHeight;

    // Créer une fenêtre temporaire avant de charger l'image
    SDL_Window* window = createWindow("Image Rotation", 800, 600);
    SDL_Renderer* renderer = createRenderer(window);

    // Charger l'image et récupérer ses dimensions
    SDL_Texture* texture = loadImage(imageFile, renderer, &imgWidth, &imgHeight);

    // Redimensionner la fenêtre à la taille de l'image
    SDL_SetWindowSize(window, imgWidth, imgHeight);

    // Boucle principale pour afficher l'image et gérer les événements
    int running = 1;
    while (running) {
        running = handleEvents();  // Gérer les événements
        displayImage(renderer, texture, imgWidth, imgHeight, angle);  // Afficher l'image
    }

    // Nettoyer les ressources et quitter
    cleanup(texture, renderer, window);

    return 0;
}
