#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sort.h"

#define PROXIMITY_THRESHOLD 10
#define OUTPUT_SIZE 32
#define OUTPUT_DIR "extracted_letters"

// Define a structure to hold bounding box properties
typedef struct
{
    int x_min, y_min;
    int x_max, y_max;
    int width, height;
    float aspect_ratio;
} BoundingBox;

SDL_Surface* load_image(const char* path)
{
    SDL_Surface * temp = IMG_Load(path);
    if (temp == NULL)
    {
        fprintf(stderr, "Error loading image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Surface * r = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_RGB888,
			0);
    SDL_FreeSurface(temp);
    return r;
}

SDL_Surface* resize_surface(SDL_Surface* surface, int new_width, int new_height)
{
    SDL_Surface* resized = SDL_CreateRGBSurfaceWithFormat(0,
		    new_width, new_height, 32, SDL_PIXELFORMAT_RGB888);
    if (!resized)
    {
        fprintf(stderr, "Error creating resized surface: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Rect src_rect = {0, 0, surface->w, surface->h};
    SDL_Rect dest_rect = {0, 0, new_width, new_height};
    SDL_BlitScaled(surface, &src_rect, resized, &dest_rect);

    return resized;
}

void save_extracted_letter(SDL_Surface* surface, BoundingBox box, 
		const char* filename) {
    SDL_Surface* letter_surface = SDL_CreateRGBSurface(0, 32, 32, 32, 
		    0x00FF0000, 0x0000FF00, 0x000000FF, 0);
    if (!letter_surface) {
        fprintf(stderr, "Error creating surface for letter: %s\n", 
			SDL_GetError());
        return;
    }

    SDL_Rect src_rect = { box.x_min, box.y_min, box.width, box.height };
    SDL_Rect dst_rect = { 0, 0, 32, 32 };
    SDL_BlitScaled(surface, &src_rect, letter_surface, &dst_rect);

    // Construct full path including the output directory
    char path[150];
    snprintf(path, sizeof(path), "%s/%s", OUTPUT_DIR, filename);

    if (IMG_SavePNG(letter_surface, path) != 0) {
        fprintf(stderr, "Error saving extracted letter: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(letter_surface);
}
// Flood-fill algorithm to label connected components
void flood_fill(Uint32* pixels, int width, int height, 
		int x, int y, int label, int* labels)
{
    int dx[] = {-1, 1, 0, 0};  // Four possible directions (up, down, left, right)
    int dy[] = {0, 0, -1, 1};

    // Initialize a queue for the flood-fill algorithm
    typedef struct { int x, y; } Point;
    Point *queue = malloc(sizeof(Point) * width * height);
    int front = 0, back = 0;
    queue[back++] = (Point){x, y};

    // Fill while the queue is not empty
    while (front < back) {
        Point p = queue[front++];
        int px = p.x;
        int py = p.y;

        int index = py * width + px;
        if (labels[index] != 0 
			|| pixels[index] != SDL_MapRGB(SDL_AllocFormat
				(SDL_PIXELFORMAT_RGB888), 255, 255, 255)) {
            continue;
        }

        // Label the current pixel
        labels[index] = label;

        // Check all directions within the threshold range
        for (int i = 0; i < 4; i++) {
            for (int d = 1; d <= PROXIMITY_THRESHOLD; d++) {
                int nx = px + dx[i] * d;
                int ny = py + dy[i] * d;

                // Make sure we're within bounds
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    int neighbor_index = ny * width + nx;
                    if (labels[neighbor_index] == 0 &&
                        pixels[neighbor_index] == 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
				255, 255, 255)) {
                        // Add neighbor to the queue
                        queue[back++] = (Point){nx, ny};
                    }
                }
            }
        }
    }
}

// Extract bounding boxes from labeled components
BoundingBox extract_bounding_box(int* labels, int width, int height, int label)
{
    BoundingBox box = {width, height, 0, 0, 0, 0, 0.0};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
	{
            if (labels[y * width + x] == label) 
	    {
                if (x < box.x_min) box.x_min = x;
                if (y < box.y_min) box.y_min = y;
                if (x > box.x_max) box.x_max = x;
                if (y > box.y_max) box.y_max = y;
            }
        }
    }

    box.width = box.x_max - box.x_min + 1;
    box.height = box.y_max - box.y_min + 1;
    box.aspect_ratio = (float)box.width / box.height;

    return box;
}
void process_letters_in_word(SDL_Surface* surface, BoundingBox word_box, 
		int word_index) {
    int width = surface->w;
    int height = surface->h;
    Uint32* pixels = (Uint32*)surface->pixels;

    int* labels = (int*)calloc(width * height, sizeof(int));
    if (!labels) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int label = 1;
    for (int y = word_box.y_min; y <= word_box.y_max; y++) {
        for (int x = word_box.x_min; x <= word_box.x_max; x++) {
            int index = y * width + x;
            if (pixels[index] == SDL_MapRGB(
				    SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
				    255, 255, 255)
			    && labels[index] == 0)
	    {
                flood_fill(pixels, width, height, x, y, label, labels);
                label++;
            }
        }
    }

    int letter_index = 0;
    for (int i = 1; i < label; i++) {
        BoundingBox letter_box = extract_bounding_box(labels, width,
				height, i);

        float aspect_ratio = letter_box.aspect_ratio;
        const float max_single_letter_aspect_ratio = 1.5;

        if (aspect_ratio > max_single_letter_aspect_ratio) {
            int estimated_letters = (int)round(aspect_ratio);
	printf("%i\n",estimated_letters);
            int sub_letter_width = letter_box.width / estimated_letters;

            for (int j = 0; j < estimated_letters; j++) {
                BoundingBox sub_box = {
                    .x_min = letter_box.x_min + j * sub_letter_width,
                    .y_min = letter_box.y_min,
                    .x_max = letter_box.x_min + (j + 1) * sub_letter_width - 1,
                    .y_max = letter_box.y_max,
                    .width = sub_letter_width,
                    .height = letter_box.height,
                    .aspect_ratio = (float)sub_letter_width / letter_box.height
                };

                char filename[100];
                snprintf(filename, sizeof(filename), "w%d_%d.png", 
				word_index, letter_index++);
                save_extracted_letter(surface, sub_box, filename);
            }
        } else {
            char filename[100];
            snprintf(filename, sizeof(filename), "w%d_%d.png", 
			    word_index, letter_index++);
            save_extracted_letter(surface, letter_box, filename);
        }
	for (int x = letter_box.x_min; x <= letter_box.x_max; x++) {
                pixels[letter_box.y_min * width + x] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					255, 0, 0);
                pixels[letter_box.y_max * width + x] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					255, 0, 0);
            }
            for (int y = letter_box.y_min; y <= letter_box.y_max; y++) {
                pixels[y * width + letter_box.x_min] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					255, 0, 0);
                pixels[y * width + letter_box.x_max] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					255, 0, 0);
            }
    }

    free(labels);
}

// Process connected components and analyze properties
void process_components(SDL_Surface* surface)
{
    int width = surface->w;
    int height = surface->h;
    Uint32* pixels = (Uint32*)surface->pixels;

    int* labels = (int*)calloc(width * height, sizeof(int));
    if (!labels) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int label = 1; // Start labeling from 1

    // Label connected components using flood fill
    for (int y = 1; y < height-1; y++)
    {
        for (int x = 1; x < width-1; x++)
	{
            int index = y * width + x;
            if (pixels[index] == SDL_MapRGB(SDL_AllocFormat(
					    SDL_PIXELFORMAT_RGB888), 
				    255, 255, 255) 
			    && labels[index] == 0) 
	    {
                flood_fill(pixels, width, height, x, y, label, labels);
                label++;
            }
        }
    }
int word_index = 0;
    // Analyze bounding boxes of each labeled component
    for (int i = 1; i < label; i++) {
        BoundingBox box = extract_bounding_box(labels, width, height, i);

	const float min_aspect_ratio_for_word = 2.5;
        // Filter based on size and aspect ratio
        if (box.width > 3 && box.height > 3 
			&& box.aspect_ratio > min_aspect_ratio_for_word)
	{
            process_letters_in_word(surface, box, word_index);
            word_index++; 
        }
	if (box.width > 2 && box.height > 10 
			&& box.width < 50 && box.height < 50 
			&& box.aspect_ratio < min_aspect_ratio_for_word)
	{
		for (int x = box.x_min; x <= box.x_max; x++) {
                pixels[box.y_min * width + x] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					0, 255, 0);
                pixels[box.y_max * width + x] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					0, 255, 0);
            }
            for (int y = box.y_min; y <= box.y_max; y++) {
                pixels[y * width + box.x_min] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					0, 255, 0);
                pixels[y * width + box.x_max] = 
			SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 
					0, 255, 0);
            }
		char filename[100];
            sprintf(filename, "g%d_%d.png", box.x_min, box.y_min);
            save_extracted_letter(surface, box, filename);
	}
    }

    free(labels);
}
