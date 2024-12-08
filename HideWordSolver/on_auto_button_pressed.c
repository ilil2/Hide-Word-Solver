#include "ANNA_graphics.h"

void on_auto_button_pressed(GtkWidget *button, gpointer user_data)
{
	button++;
	GtkBuilder *builder = GTK_BUILDER(user_data);
	GtkImage *image = GTK_IMAGE(gtk_builder_get_object(builder, "SBSImage"));

	SDL_Surface *surface = IMG_Load("image.png");
	double angle = detectRotationAngle(surface);
	printf("%f\n", angle);
	save_image("image.png", "image2.png", angle);
	gtk_image_set_from_file(image, "image2.png");
	resize_image(image);
	SDL_FreeSurface(surface);
}
