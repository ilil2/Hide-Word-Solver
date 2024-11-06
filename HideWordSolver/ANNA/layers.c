#include "neural_network.h"

void layers(size_t nb_letter,
		float **input,
		float **output)
{
	float **temp_output = malloc(sizeof(float*) * image_size * image_size);
	for (size_t i = 0; i < image_size * image_size; i++)
	{
		temp_output[i] = malloc(sizeof(float) * nb_letter);
	}

	float div = (float)1/(float)9;

	float filter1[] = {div, div, div, 
						div, div, div,
						div, div, div};
	float filter2[] = {0, -1, 0,
						-1, 5, -1,
						0, -1, 0};

	// Apply convolution layers
	convolution(nb_letter, input, temp_output, filter1, filter2);

	for (size_t i = 0; i < image_size * image_size; i++)
	{
		for (size_t j = 0; j < nb_letter; j++)
		{
			temp_output[i][j] = activ(temp_output[i][j]);
		}
	}

	// Apply pooling layers
	pooling(nb_letter, temp_output, 8, output);

	for (size_t i = 0; i < image_size * image_size; i++)
	{
		free(temp_output[i]);
	}
	free(temp_output);
}
