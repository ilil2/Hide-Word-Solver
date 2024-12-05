#include "draw.h"

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("usage : ./draw {image_path} {x1} {y1} {x2} {y2}\n");
		return 1;
	}

	draw_line(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
	return 0;
}
