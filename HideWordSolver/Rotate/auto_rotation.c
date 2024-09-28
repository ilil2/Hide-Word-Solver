#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>

#define SOBEL_SIZE 3

// Create an SDL window
SDL_Window* create_window(const char* title, int width, int height)
{
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

// Create an SDL renderer
SDL_Renderer* create_renderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return renderer;
}

// Load image as SDL texture
SDL_Texture* load_image_as_texture(SDL_Renderer* renderer, const char* file)
{
    SDL_Surface* image = IMG_Load(file);
    if (!image)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(image);
    return texture;
}

// Apply the Sobel operator to detect edges and calculate the angle
double detectRotationAngle(SDL_Surface* image)
{
    int width = image->w;
    int height = image->h;

    // Allocate memory for gradient arrays
    double* gradient_x = (double*)malloc(width * height * sizeof(double));
    double* gradient_y = (double*)malloc(width * height * sizeof(double));
    double* angles = (double*)malloc(width * height * sizeof(double));

    // Sobel kernel for x and y directions
    int sobel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int sobel_y[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    // Compute gradients
    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            double gx = 0;
            double gy = 0;

            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    Uint32 pixel = *((Uint32*)image->pixels + (y + ky) * width + (x + kx));
                    Uint8 r, g, b;
                    SDL_GetRGB(pixel, image->format, &r, &g, &b);
                    double intensity = 0.299 * r + 0.587 * g + 0.114 * b; // Convert to grayscale

                    gx += sobel_x[ky + 1][kx + 1] * intensity;
                    gy += sobel_y[ky + 1][kx + 1] * intensity;
                }
            }

            gradient_x[y * width + x] = gx;
            gradient_y[y * width + x] = gy;
            angles[y * width + x] = atan2(gy, gx) * (180.0 / M_PI); // Angle in degrees
        }
    }

    // Analyze angles to determine the predominant angle
    double total_angle = 0;
    int count = 0;

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            if (gradient_x[y * width + x] != 0 || gradient_y[y * width + x] != 0)
            {
                total_angle += angles[y * width + x];
                count++;
            }
        }
    }

    double average_angle = count > 0 ? total_angle / count : 0;

    // Clean up
    free(gradient_x);
    free(gradient_y);
    free(angles);

    return average_angle; // Return the detected rotation angle
}

// Handle SDL events
void handle_events(int* quit)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            *quit = 1;
        }
    }
}

int main(int argc, char* argv[])
{
    // Ensure image file is provided
    if (argc != 2)
    {
        errx(EXIT_FAILURE, "Usage: %s <image_file>", argv[0]);
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("Error initializing SDL_image: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Load the image
    SDL_Surface* image = IMG_Load(argv[1]);
    if (!image)
    {
        printf("Error loading image: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Detect rotation angle
    double angle = detectRotationAngle(image);

    // Create window matching image size
    SDL_Window* window = create_window("Image Rotation Auto", image->w, image->h);

    // Create renderer
    SDL_Renderer* renderer = create_renderer(window);

    // Convert surface to texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    // Main event loop
    int quit = 0;
    while (!quit)
    {
        // Handle events
        handle_events(&quit);

        // Clear renderer
        SDL_RenderClear(renderer);

        // Copy texture with rotation
        SDL_RenderCopyEx(renderer, texture, NULL, NULL, angle, NULL, SDL_FLIP_NONE);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
