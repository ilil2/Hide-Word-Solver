#include "ANNA_graphics.h"

extern int state;

void next_solver(GtkWidget *button, gpointer user_data)
{
	if (state == 0)
	{
		//call GrayScale
	}
	else if (state == 1)
	{
		//call InvColor
	}
	else if (state == 2)
	{
		//call Rotate
	}
	else if (state == 3)
	{
		//call Cropping
	}
	else if (state == 4)
	{
		//call ANNA + Solver
	}
	state++;
}
