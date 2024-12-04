#include "neural_network.h"

void load_dataset(char *file_path,
        int file_nb,
        ANNA* anna)
{
    FILE* image_file = NULL;

	image_file = fopen(file_path, "r");

    // Load image
    if (image_file != NULL)
    {
        
    }
    else
    {
		printf("Error opening files.\n");
    }

	fclose(image_file);
}