#include "neural_network.h"

void convert_output_to_char(int nb_letter,
		double **output, // output_neuron x nb_letter
		char *anna_result) // nb_letter
{

	for (int i = 1; i < nb_letter; i++)
	{
		double max = output[0][i];
		size_t jmax = 0;
		for (size_t j = 0; j < output_neuron; j++)
		{
			if (output[j][i] > max)
			{
				jmax = j;
			}
		}
		anna_result[i] = 'A' + jmax;
	}
}
