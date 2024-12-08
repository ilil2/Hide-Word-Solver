 #include "ANNA_graphics.h"

extern char state;

// Do the next step on StepByStep mode
void next_solver(GtkWidget *button, gpointer user_data)
{
	button++;
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
	if (surface == NULL)
		err(1, "IMG_Load()\n");

	char **markup = malloc(sizeof(char *));
	GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "SBSList"));

	if (state == 0)
	{
		surface = preprocess_image(surface);
		IMG_SavePNG(surface, "image.png");
		IMG_SavePNG(surface, "image2.png");
		gtk_image_set_from_file(image, "image.png");

		GtkWidget *rotation_grid =
            GTK_WIDGET(gtk_builder_get_object(builder,
                "SBSRotationGrid"));
        gtk_widget_show(rotation_grid);

		*markup =
			"<span foreground='green'>• Binarization</span>\n"
			"<span foreground='white'>• <b>Rotation</b></span>\n"
			"<span foreground='red'>• Detection</span>\n"
			"<span foreground='red'>• Solver</span>\n";

	}
	else if (state == 1)
	{
		GtkWidget *rotation_grid =
            GTK_WIDGET(gtk_builder_get_object(builder,
                "SBSRotationGrid"));
        gtk_widget_hide(rotation_grid);
		
		SDL_FreeSurface(surface);
		surface = IMG_Load("image2.png");
		//median_filter(surface);
		IMG_SavePNG(surface, "image.png");

		*markup =
			"<span foreground='green'>• Binarization</span>\n"
			"<span foreground='green'>• Rotation</span>\n"
			"<span foreground='white'>• <b>Detection</b></span>\n"
			"<span foreground='red'>• Solver</span>\n";
	}
	else if (state == 2)
	{
		SDL_FreeSurface(surface);
		SDL_Init(SDL_INIT_VIDEO);
		surface = IMG_Load("image.png");
		SDL_Surface * surface2 = SDL_ConvertSurfaceFormat(surface,
				SDL_PIXELFORMAT_RGB888, 0);
		process_components(surface2);
		IMG_SavePNG(surface2, "image.png");
		gtk_image_set_from_file(image, "image.png");
		SDL_Quit();
		SDL_FreeSurface(surface2);

		*markup =
			"<span foreground='green'>• Binarization</span>\n"
			"<span foreground='green'>• Rotation</span>\n"
			"<span foreground='green'>• Detection</span>\n"
			"<span foreground='white'>• <b>Solver</b></span>\n";
	}
	else if (state == 3)
	{
		// Call ANNA + Solver

		*markup =
			"<span foreground='green'>• Binarization</span>\n"
			"<span foreground='green'>• Rotation</span>\n"
			"<span foreground='green'>• Detection</span>\n"
			"<span foreground='green'>• Solver</span>\n";
	}
	else
	{
		gtk_stack_set_visible_child_name(stack, "page3");

		*markup = "";
	}
	resize_image(image);
	gtk_label_set_markup(label, *markup);
	SDL_FreeSurface(surface);
	free(markup);
	state++;
}
