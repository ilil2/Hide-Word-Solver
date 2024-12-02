#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
// #include "../ANNA_graphics.h"
#include "rotation.h"
#include "../Preprocessing/medianfilter.h"




// Fonction pour afficher la surface (image)
void display_surface(SDL_Surface* surface, int delay_ms)
{
    SDL_Window* window = SDL_CreateWindow("Image Display",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          surface->w,
                                          surface->h,
                                          SDL_WINDOW_SHOWN);

    if (!window)
        errx(EXIT_FAILURE, "Window creation failed: %s", SDL_GetError());

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        errx(EXIT_FAILURE, "Renderer creation failed: %s", SDL_GetError());

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
        errx(EXIT_FAILURE, "Texture creation failed: %s", SDL_GetError());

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(delay_ms);  // Affiche l'image pendant un maximum de 2 secondes

    // Libération des ressources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

// Fonction pour appliquer le prétraitement (grayscale, Otsu, et median filter)
SDL_Surface* preprocess_image(SDL_Surface* surface)
{
    // Conversion en niveaux de gris
    surface_to_grayscale(surface);

    Uint32* pixels = surface->pixels;
    int len = surface->w * surface->h;
    Uint8 threshold = otsus(len, pixels, surface->format);  // Application de l'algorithme Otsu
    surface_to_black_and_white(surface, threshold);         // Application du seuillage en noir et blanc
    median_filter(surface);                                 // Application du filtre médian

    return surface;
}

// Fonction de détection de l'angle de rotation (exemple utilisant la transformée de Hough)
double detectRotationAngle(SDL_Surface* surface)
{
    // Ici, tu peux utiliser la fonction de transformée de Hough que tu as déjà définie
    // Pour simplifier, on retourne un angle arbitraire pour l'exemple
    return 45.0;  // Un angle de 45 degrés comme exemple
}

// Fonction principale pour charger, traiter et afficher l'image
void auto_rotate(const char* image_path)
{
    SDL_Surface* surface = IMG_Load(image_path);
    if (!surface)
        errx(EXIT_FAILURE, "Image loading failed: %s", IMG_GetError());

    // Affiche l'image originale pendant 2 secondes
    display_surface(surface, 2000);

    // Prétraitement de l'image
    SDL_Surface* preprocessed_surface = preprocess_image(surface);

    // Affiche l'image prétraitée pendant 2 secondes
    display_surface(preprocessed_surface, 2000);

    // Détection de l'angle de rotation
    double angle = detectRotationAngle(preprocessed_surface);

    // Créer une texture à partir de la surface prétraitée
    SDL_Window* window = SDL_CreateWindow("Rotated Image",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          preprocessed_surface->w,
                                          preprocessed_surface->h,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, preprocessed_surface);

    if (!texture)
        errx(EXIT_FAILURE, "Texture creation failed: %s", SDL_GetError());

    // Rotation de l'image en utilisant SDL_RenderCopyEx
    SDL_RenderClear(renderer);
    SDL_RenderCopyEx(renderer, texture, NULL, NULL, angle, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);  // Afficher l'image tournée pendant 2 secondes

    // Libération des ressources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Libération de la surface prétraitée
    SDL_FreeSurface(surface);
    SDL_FreeSurface(preprocessed_surface);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: %s <image_path>", argv[0]);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        errx(EXIT_FAILURE, "SDL could not initialize: %s", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG & IMG_INIT_JPG))
        errx(EXIT_FAILURE, "SDL_image could not initialize: %s", IMG_GetError());

    // Lancer la rotation automatique de l'image
    auto_rotate(argv[1]);

    // Nettoyage
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
