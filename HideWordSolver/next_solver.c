 #include "ANNA_graphics.h"

extern char state;

// Do the next step on StepByStep mode
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
		IMG_SavePNG(surface, "image2.png");
		gtk_image_set_from_file(image, "image.png");

		GtkWidget *spin_button =
            GTK_WIDGET(gtk_builder_get_object(builder,
                "SBSRotationAngle"));
        gtk_widget_show(spin_button);
	}
	else if (state == 1)
	{
		GtkWidget *spin_button =
            GTK_WIDGET(gtk_builder_get_object(builder,
                "SBSRotationAngle"));
        gtk_widget_hide(spin_button);
		
		SDL_FreeSurface(surface);
		surface = IMG_Load("image2.png");
		IMG_SavePNG(surface, "image.png");
	}
	else if (state == 2)
	{
		SDL_FreeSurface(surface);
		SDL_Init(SDL_INIT_VIDEO);
		surface = load_image("image.png");
		process_components(surface);
		IMG_SavePNG(surface, "image.png");
		gtk_image_set_from_file(image, "image.png");
		SDL_Quit();
	}
	else if (state == 3)
	{
		// Call ANNA + Solver
	}
	SDL_FreeSurface(surface);
	state++;
}
