#ifndef EXTRACTION_H
#define EXTRACTION_H

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

typedef struct
{
    int x_min, y_min;
    int x_max, y_max;
    int width, height;
    float aspect_ratio;
} BoundingBox;

SDL_Surface* resize_surface(SDL_Surface* surface, int new_width, 
		int new_height);

void save_extracted_letter(SDL_Surface* surface, BoundingBox box,
                const char* filename);

void flood_fill(Uint32* pixels, int width, int height,
                int x, int y, int label, int* labels);

BoundingBox extract_bounding_box(int* labels, int width, int height, int label);

void process_letters_in_word(SDL_Surface* surface, BoundingBox word_box,
                int word_index);

void process_components(SDL_Surface* surface);

#endif
