#include "ANNA_graphics.h"

void on_save_button_pressed(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkResponseType response;

    dialog = gtk_file_chooser_dialog_new("Save File",
                                         GTK_WINDOW(user_data),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         "_Save", GTK_RESPONSE_ACCEPT,
                                         NULL);

    chooser = GTK_FILE_CHOOSER(dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    gtk_file_chooser_set_current_name(chooser, "result.png");

    response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT)
	{
        char *filename;

        filename = gtk_file_chooser_get_filename(chooser);

        SDL_Surface *surface = IMG_Load("image.png");
		IMG_SavePNG(surface, filename);

		SDL_FreeSurface(surface);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

