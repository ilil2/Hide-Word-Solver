#include "neural_network.h"

char convert_output_to_char(double *output)
{
	double max = output[0];
	size_t imax = 0;

	for (size_t i = 1; i < output_neuron; i++)
	{
		if (output[i] > max)
		{
			imax = i;
		}
	}

	return 'A' + imax;
}
