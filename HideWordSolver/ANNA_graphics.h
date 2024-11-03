#ifndef __ANNA_GRAPHICS_H__
#define __ANNA_GRAPHICS_H__

#include <gtk/gtk.h>
#include <stdio.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "Rotate/rotation.h"
#include "Preprocessing/binarization.h"
#include "Preprocessing/medianfilter.h"
#include "Preprocessing/grayscale.h"
#include "Preprocessing/sobel.h"

void on_start_button_pressed(GtkWidget *button, gpointer user_data);
void make_signals(GtkBuilder *builder);
void next_solver(GtkWidget *button, gpointer user_data);
GdkPixbuf *sdl_surface_to_pixbuf(SDL_Surface *surface);
SDL_Surface* preprocess_image(SDL_Surface* surface);
void on_spinbutton_value_changed(GtkSpinButton *spin_button,
                gpointer user_data);
void process_components(SDL_Surface* surface);
SDL_Surface* load_image(const char* path);
void on_size_allocate(GtkWidget *widget, GdkRectangle *allocation,
		gpointer user_data);

#endif
