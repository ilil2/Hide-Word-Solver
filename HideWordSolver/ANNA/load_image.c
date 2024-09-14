#include "neural_network.h"

void load_image(const char *image_path, size_t file_size,
        double image[file_size][input_neuron])
{
    FILE* file_image = NULL;
    
	file_image = fopen(image_path, "r");

    if(file_image != NULL)
    {
        for (size_t i = 0; i < file_size; i++)
        {
            for (size_t j = 0; j < input_neuron; j++)
            {
                fscanf(file_image, "%lf,", &image[i][j]);
            }
        }
    }
    else
    {
		printf("Error opening %s files.", image_path);
    }

	fclose(file_image);
}