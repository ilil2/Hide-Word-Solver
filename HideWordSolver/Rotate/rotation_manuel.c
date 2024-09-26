#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to initialize SDL and create a window
SDL_Window* createWindow(const char* title, int width, int height) {
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1); // Exit on error
    }
    return window;
}

// Function to create a renderer
SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1); // Exit on error
    }
    return renderer;
}

// Function to load the image and create a texture
SDL_Texture* loadImage(const char* file, SDL_Renderer* renderer, int* width, int* height) {
    SDL_Surface* surface = IMG_Load(file);  // Load the image
    if (!surface) {
        fprintf(stderr, "Error loading image %s: %s\n", file, IMG_GetError());
        SDL_Quit();
        exit(1); // Exit on error
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_Quit();
        exit(1); // Exit on error
    }

    // Get image width and height
    *width = surface->w;
    *height = surface->h;

    SDL_FreeSurface(surface);  // Free surface after texture creation
    return texture;
}

// Function to display the image with rotation
void displayImage(SDL_Renderer* renderer, SDL_Texture* texture, int imgWidth, int imgHeight, double angle) {
    // Clear the screen
    SDL_RenderClear(renderer);

    // Set rotation center to the image center
    SDL_Point center = { imgWidth / 2, imgHeight / 2 };

    // Set render area in the window
    SDL_Rect destRect = { 0, 0, imgWidth, imgHeight };

    // Apply rotation and display the image
    SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle, &center, SDL_FLIP_NONE);

    // Update the display
    SDL_RenderPresent(renderer);
}

// Function to handle events (window close)
int handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 0;  // Exit the application
        }
    }
    return 1;  // Continue running
}

// Function to clean up and free resources
void cleanup(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window) {
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <image_file> <rotation_angle>\n", argv[0]);
        return 1;
    }

    const char* imageFile = argv[1];  // Image file path
    double angle = atof(argv[2]);     // Rotation angle

    // Initialize SDL and SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        fprintf(stderr, "SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    int imgWidth, imgHeight;

    // Create a temporary window before loading the image
    SDL_Window* window = createWindow("Image Rotation", 800, 600);
    SDL_Renderer* renderer = createRenderer(window);

    // Load the image and get its dimensions
    SDL_Texture* texture = loadImage(imageFile, renderer, &imgWidth, &imgHeight);

    // Resize the window to the image size
    SDL_SetWindowSize(window, imgWidth, imgHeight);

    // Main loop to display the image and handle events
    int running = 1;
    while (running) {
        running = handleEvents();  // Handle events
        displayImage(renderer, texture, imgWidth, imgHeight, angle);  // Display the image
    }

    // Clean up resources and exit
    cleanup(texture, renderer, window);

    return 0;
}
