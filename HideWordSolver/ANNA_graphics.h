#ifndef __ANNA_GRAPHICS_H__
#define __ANNA_GRAPHICS_H__

#include <gtk/gtk.h>
#include <stdio.h>
#include <stddef.h>

void on_start_button_pressed(GtkWidget *button, gpointer user_data);
void make_signals(GtkBuilder *builder);
void next_solver(GtkWidget *button, gpointer user_data);

#endif
