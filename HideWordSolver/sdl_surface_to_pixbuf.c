#include "ANNA_graphics.h"

GdkPixbuf *sdl_surface_to_pixbuf(SDL_Surface *surface)
{
    int width = surface->w;
    int height = surface->h;
    int rowstride = surface->pitch;
    gboolean has_alpha = surface->format->BytesPerPixel == 4;

    return gdk_pixbuf_new_from_data(
        (guchar*)surface->pixels,
        GDK_COLORSPACE_RGB,
        has_alpha,
        8,
        width,
        height,
        rowstride,
        NULL,
        NULL
    );
}
