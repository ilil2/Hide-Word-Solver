#ifndef AUTO_ROTATION_H
#define AUTO_ROTATION_H

#include <SDL2/SDL.h>

double detectRotationAngle(SDL_Surface* image);
void auto_rotate(const char* image_path);

#endif // AUTO_ROTATION_H
