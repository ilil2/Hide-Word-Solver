#include "ANNA_graphics.h"

// Call when start button is pressed
void on_start_button_pressed(GtkWidget *button, gpointer user_data)
{
	button++;
	GtkBuilder* builder = GTK_BUILDER(user_data);
	GtkFileChooser* file_chooser = GTK_FILE_CHOOSER(
			gtk_builder_get_object(builder, "ImageChooser"));

	GtkStack* stack = GTK_STACK(gtk_builder_get_object(builder, "Stack"));
	GtkSwitch* switch_ = GTK_SWITCH(gtk_builder_get_object(builder, "Switch"));
	GtkImage* image;

	GFile* image_file = gtk_file_chooser_get_file(file_chooser);
	gboolean active = gtk_switch_get_active(switch_);

	if (image_file != NULL)
	{
		gchar* path = g_file_get_path(image_file);
		SDL_Surface *sdl_surface = IMG_Load(path);
		SDL_Surface* optimized_surface =
			SDL_ConvertSurfaceFormat(sdl_surface, SDL_PIXELFORMAT_ARGB8888, 0);
		IMG_SavePNG(optimized_surface, "image.png");
		GdkPixbuf *pixbuf = sdl_surface_to_pixbuf(sdl_surface);

		if (active)
		{
	 		image = GTK_IMAGE(gtk_builder_get_object(builder, "SBSImage"));
			gtk_stack_set_visible_child_name(stack, "page2");

			GtkWidget *rotation_grid =
				GTK_WIDGET(gtk_builder_get_object(builder,
							"SBSRotationGrid"));
			gtk_widget_hide(rotation_grid);
		}
		else
		{
			image = GTK_IMAGE(gtk_builder_get_object(builder, "SolverImage"));
			gtk_stack_set_visible_child_name(stack, "page1");
		}
		
		gtk_image_set_from_pixbuf(image, pixbuf);
		gtk_image_set_pixel_size(image, 500);

		resize_image(image);

		char **markup = malloc(sizeof(char *));
		GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder, "SBSList"));

		*markup =
                        "<span foreground='white'>• <b>Binarization</b></span>\n"
                        "<span foreground='red'>• Rotation</span>\n"
                        "<span foreground='red'>• Detection</span>\n"
                        "<span foreground='red'>• Solver</span>\n";

		gtk_label_set_markup(label, *markup);


		// Free
		g_object_unref(pixbuf);
		g_free(path);
		SDL_FreeSurface(sdl_surface);
		SDL_FreeSurface(optimized_surface);
		free(markup);
	}
}
