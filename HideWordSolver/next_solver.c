#include "ANNA_graphics.h"

extern int state;

void next_solver(GtkWidget *button, gpointer user_data)
{
	GtkBuilder* builder = GTK_BUILDER(user_data);
	GtkStack* stack = GTK_STACK(gtk_builder_get_object(builder, "Stack"));
	const gchar *current_page_name = gtk_stack_get_visible_child_name(stack);

	GtkImage* image;
	if (current_page_name[4] == '2')
    {
    	image = GTK_IMAGE(gtk_builder_get_object(builder, "SBSImage"));
    }
    else
    {
        image = GTK_IMAGE(gtk_builder_get_object(builder, "SolverImage"));
    }

	if (!image) {
        g_printerr("Erreur : Impossible de récupérer l'image.\n");
        return;
    }


	if (state == 0)
	{
		GdkPixbuf *pixbuf = gtk_image_get_pixbuf(image);
		if (!pixbuf) {
            g_printerr("Erreur : GdkPixbuf est NULL. L'image n'a peut-être pas été définie avec un GdkPixbuf.\n");
            return;
        }
		gdk_pixbuf_save(pixbuf, "image.png", "png", NULL, NULL);
		SDL_Surface* surface = IMG_Load("image.png");
		surface = preprocess_image(surface);
		GdkPixbuf *pixbuf2 = sdl_surface_to_pixbuf(surface);
		gtk_image_set_from_pixbuf(image, pixbuf2);
	}
	else if (state == 1)
	{
		//call Rotate
	}
	else if (state == 2)
	{
		//call Cropping
	}
	else if (state == 3)
	{
		//call ANNA + Solver
	}
	state++;
}
