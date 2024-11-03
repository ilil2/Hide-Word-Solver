#include "ANNA_graphics.h"

// For resize
void on_size_allocate(GtkWidget *widget, GdkRectangle *allocation,
		gpointer user_data)
{
	GtkBuilder *builder = (GtkBuilder*)user_data;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("image.png", NULL);
	GtkImage *image;
	image = GTK_IMAGE(gtk_builder_get_object(builder, "SBSImage"));

    GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf,
			allocation->width, allocation->height, GDK_INTERP_BILINEAR);

    gtk_image_set_from_pixbuf(image, scaled_pixbuf);
    g_object_unref(scaled_pixbuf);
}
