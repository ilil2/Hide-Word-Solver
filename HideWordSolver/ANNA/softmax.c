#include "neural_network.h"

void softmax(int nb_letter, float **output)
{
	for (int n = 0; n < nb_letter; n++)
    {
        float max = output[0][n];
        for (int i = 1; i < output_neuron; i++)
        {
            if (output[i][n] > max)
            {
                max = output[i][n];
            }
        }

        float sum = 0.0;
        for (int i = 0; i < output_neuron; i++)
        {
            output[i][n] = exp(output[i][n] - max);
            sum += output[i][n];
        }

        for (int i = 0; i < output_neuron; i++)
        {
            output[i][n] /= sum;
        }
    }
}
