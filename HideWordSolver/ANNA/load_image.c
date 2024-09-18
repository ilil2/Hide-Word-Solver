#include "neural_network.h"

void load_image(const char *csv_path, size_t file_size,
        double **image) //input_neuron x file_size
{
    FILE* file_image = NULL;
    
	file_image = fopen(csv_path, "r");

    if(file_image != NULL)
    {
        for (size_t i = 0; i < input_neuron; i++)
        {
            for (size_t j = 0; j < file_size; j++)
            {
                fscanf(file_image, "%lf,", &image[i][j]);
                image[i][j] /= 255.0;
            }
        }
    }
    else
    {
		printf("Error opening %s files.\n", csv_path);
    }

	fclose(file_image);
}
