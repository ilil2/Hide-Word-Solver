#include "ANNA_graphics.h"

void make_signals(GtkBuilder *builder)
{
	// Start button
	GtkButton* start_button;
	start_button = GTK_BUTTON(gtk_builder_get_object(builder, "Start"));
	
	g_signal_connect(start_button, "clicked",
			G_CALLBACK(on_start_button_pressed), builder);

	// SBSNext button
	GtkButton* sbsnext_button;
	sbsnext_button = GTK_BUTTON(gtk_builder_get_object(builder, "SBSNext"));

	g_signal_connect(sbsnext_button, "clicked",
			G_CALLBACK(next_solver), builder);
}
