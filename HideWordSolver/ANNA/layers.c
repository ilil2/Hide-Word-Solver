#include "neural_network.h"

void layers(size_t nb_letter,
		double **input,
		double **output)
{
	double **temp_output = malloc(sizeof(double*) * image_size * image_size);
	for (size_t i = 0; i < image_size * image_size; i++)
	{
		temp_output[i] = malloc(sizeof(double) * nb_letter);
	}

	double div = (double)1/(double)9;

	double filter1[] = {div, div, div, 
						div, div, div,
						div, div, div};
	double filter2[] = {0, -1, 0,
						-1, 5, -1,
						0, -1, 0};

	convolution(nb_letter, input, temp_output, filter1, filter2);

	for (size_t i = 0; i < image_size * image_size; i++)
	{
		for (size_t j = 0; j < nb_letter; j++)
		{
			temp_output[i][j] = activ(temp_output[i][j]);
		}
	}

	pooling(nb_letter, temp_output, 8, output);

	for (size_t i = 0; i < image_size * image_size; i++)
	{
		free(temp_output[i]);
	}
	free(temp_output);
}
