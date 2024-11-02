#ifndef ROTATION_H
#define ROTATION_H

#include <SDL2/SDL.h>         
#include <SDL2/SDL_image.h>

void auto_rotate(const char* image_path);

void manual_rotate(const char* image_path, float angle);

SDL_Window *create_window(char* title, unsigned width, unsigned height);
SDL_Renderer* create_renderer(SDL_Window* window);
SDL_Texture* load_image_as_texture(SDL_Renderer* renderer, const char* file);

void display_image(const char* image_path, float angle);
void save_image(const char* image_path, const char* save_path, float angle);

double detectRotationAngle(SDL_Surface* image);

#endif
