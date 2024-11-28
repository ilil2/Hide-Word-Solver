#include "ANNA_graphics.h"

void resize_image(GtkImage *image_widget) {
    // Récupérer le GdkPixbuf actuel depuis GtkImage
    GdkPixbuf *pixbuf = gtk_image_get_pixbuf(image_widget);
    if (!pixbuf) {
        g_printerr("Aucune image n'est actuellement associée au widget GtkImage.\n");
        return;
    }

    // Récupérer les dimensions actuelles de l'image
    int width = gdk_pixbuf_get_width(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);

    // Vérifier si une redimension est nécessaire
    if (width > 1000 || height > 500) {
        double scale = width > 2 * height ? 500.0 / width : 1000.0 / height;
        int new_width = width * scale;
        int new_height = height * scale;

        // Redimensionner l'image
        GdkPixbuf *resized_pixbuf = gdk_pixbuf_scale_simple(
            pixbuf, new_width, new_height, GDK_INTERP_BILINEAR);

        if (resized_pixbuf) {
            // Mettre à jour le GtkImage avec l'image redimensionnée
            gtk_image_set_from_pixbuf(image_widget, resized_pixbuf);

            // Libérer les ressources
            g_object_unref(resized_pixbuf);
        }
    }
}
