#include "neural_network.h"

void convert_output_to_char(size_t nb_letter,
		size_t output_neuron,
		float **output, // output_neuron x nb_letter
		char *anna_result) // nb_letter
{
	// Converts a matrix of 1's and 0's into char
	for (size_t i = 0; i < nb_letter; i++)
    {
        float max = output[0][i];
        size_t jmax = 0;
        for (size_t j = 1; j < output_neuron; j++)
        {
			//printf("%f\n", output[j][i]);
            if (output[j][i] > max)
            {
                max = output[j][i];
                jmax = j;
            }
        }
		//printf("\n");

		if (jmax < 26)
		{
			// Capital letter
			anna_result[i] = 'A' + jmax;
		}
		else if (jmax < 52)
		{
			// Lowercase letter
			anna_result[i] = 'a' + (jmax - 26);
		}
		else
		{
			anna_result[i] = '?';
		}
		
	}
}
