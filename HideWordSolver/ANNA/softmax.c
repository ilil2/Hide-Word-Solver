#include "neural_network.h"
#include <math.h>

void softmax(int nb_letter, double **output)
{
	for (size_t i = 0; i < output_neuron; i++)
	{
		double sum = 0;
		for (size_t j = 0; j < (size_t)nb_letter; j++)
		{
			sum += exp(output[i][j]);
		}
		for (size_t j = 0; j < (size_t)nb_letter; j++)
		{
			output[i][j] = exp(output[i][j]) / sum;
		}
	}
}
