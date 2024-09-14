#ifndef __MAIN_DATASET_H__
#define __MAIN_DATASET_H__

#include <SDL2/SDL.h>
#include "../neural_network.h"

void add_to_dataset(const char *img, const char *csv);
void bmp_to_csv(const SDL_Surface *tmp, const char *csv);

#endif