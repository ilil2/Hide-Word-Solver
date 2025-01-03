#include "ANNA_graphics.h"


// Connect all signals of ANNA
void make_signals(GtkBuilder *builder)
{
	// Window
	GtkWidget *window;
	window = GTK_WIDGET(gtk_builder_get_object(builder, "ANNA"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
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

	// SBSRotationAngle spin button
	GtkSpinButton *spin_button;
	spin_button = GTK_SPIN_BUTTON(gtk_builder_get_object(builder,
				"SBSRotationAngle"));

	g_signal_connect(spin_button, "value-changed",
			G_CALLBACK(on_spinbutton_value_changed), builder);

	// SBSAutoButton button
	GtkButton *sbsauto_button;
	sbsauto_button = GTK_BUTTON(gtk_builder_get_object(builder,
				"SBSAutoButton"));

	g_signal_connect(sbsauto_button, "clicked",
			G_CALLBACK(on_auto_button_pressed), builder);

	// SaveButton button
	GtkButton *save_button;
	save_button = GTK_BUTTON(gtk_builder_get_object(builder, "SaveButton"));

	g_signal_connect(save_button, "clicked",
			G_CALLBACK(on_save_button_pressed), NULL);
}
