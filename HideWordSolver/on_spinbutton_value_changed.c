#include "ANNA_graphics.h"

// Call when rotation degree change
void on_spinbutton_value_changed(GtkSpinButton *spin_button,
		gpointer user_data)
{
	GtkBuilder* builder = GTK_BUILDER(user_data);
	GtkImage *image;
	image = GTK_IMAGE(gtk_builder_get_object(builder, "SBSImage"));
	double angle = gtk_spin_button_get_value(spin_button);
    save_image("image.png", "image2.png", angle);
    gtk_image_set_from_file(image, "image2.png");
	resize_image(image);
}
