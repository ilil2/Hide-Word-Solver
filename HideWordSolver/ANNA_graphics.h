#ifndef __ANNA_GRAPHICS_H__
#define __ANNA_GRAPHICS_H__

#include <gtk/gtk.h>
#include <stdio.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "Rotate/rotation.h"
#include "Preprocessing/preprocessing.h"
#include "Preprocessing/medianfilter.h"

void on_start_button_pressed(GtkWidget *button, gpointer user_data);
void make_signals(GtkBuilder *builder);
void next_solver(GtkWidget *button, gpointer user_data);
GdkPixbuf *sdl_surface_to_pixbuf(SDL_Surface *surface);
SDL_Surface* preprocess_image(SDL_Surface* surface);
void on_spinbutton_value_changed(GtkSpinButton *spin_button,
                gpointer user_data);
void process_components(SDL_Surface* surface);
SDL_Surface* load_image(const char* path);

#endif
