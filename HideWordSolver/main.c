#include "ANNA_graphics.h"

char state;

int main(int argc, char **argv)
{
	GtkBuilder* builder;
	GtkWidget* window;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file("ANNA.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "ANNA"));

	state = 0;

	make_signals(builder);

	gtk_widget_show_all(window);

	gtk_main();

	g_object_unref(builder);

	return 0;
}
