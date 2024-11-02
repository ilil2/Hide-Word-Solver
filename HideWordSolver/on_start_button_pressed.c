#include "ANNA_graphics.h"

//extern char* file;

void on_start_button_pressed(GtkWidget *button, gpointer user_data)
{
	GtkBuilder* builder = GTK_BUILDER(user_data);
	GtkFileChooser* file_chooser = GTK_FILE_CHOOSER(
			gtk_builder_get_object(builder, "ImageChooser"));
	//file = gtk_file_chooser_get_preview_filename(file_chooser);

	GtkStack* stack = GTK_STACK(gtk_builder_get_object(builder, "Stack"));
	GtkSwitch* switch_ = GTK_SWITCH(gtk_builder_get_object(builder, "Switch"));
	GtkImage* image;

	GFile* image_file = gtk_file_chooser_get_file(file_chooser);
	gboolean active = gtk_switch_get_active(switch_);

	if (image_file != NULL)
	{
		gchar* path = g_file_get_path(image_file);
		SDL_Surface *sdl_surface = IMG_Load(path);
		IMG_SavePNG(sdl_surface, "image.png");
		GdkPixbuf *pixbuf = sdl_surface_to_pixbuf(sdl_surface);

		if (active)
		{
	 		image = GTK_IMAGE(gtk_builder_get_object(builder, "SBSImage"));
			gtk_stack_set_visible_child_name(stack, "page2");
		}
		else
		{
			image = GTK_IMAGE(gtk_builder_get_object(builder, "SolverImage"));
			gtk_stack_set_visible_child_name(stack, "page1");
		}
		
		gtk_image_set_from_pixbuf(image, pixbuf);
		gtk_image_set_pixel_size(image, 500);
		g_object_unref(pixbuf);
		g_free(path);
	}
}
