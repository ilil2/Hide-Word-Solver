#include "ANNA_graphics.h"

extern char state;

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

	SDL_Surface* surface = IMG_Load("image.png");

	if (state == 0)
	{
		surface = preprocess_image(surface);
		IMG_SavePNG(surface, "image.png");
		gtk_image_set_from_file(image, "image.png");
	}
	else if (state == 1)
	{
		double angle = detectRotationAngle(surface);
		save_image("image.png", angle);
		gtk_image_set_from_file(image, "image.png");
	}
	else if (state == 2)
	{
		//call Cropping
	}
	else if (state == 3)
	{
		//call ANNA + Solver
	}
	SDL_FreeSurface(surface);
	state++;
}
