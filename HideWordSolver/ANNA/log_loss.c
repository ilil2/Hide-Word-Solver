#include "neural_network.h"

float log_loss(int nb_letter,
                float **expected_output, // output_neuron x nb_letter
                float **output) // output_neuron x nb_letter
{
    float sum;
    float epsilon = 1e-15;
    for (size_t i = 0; i < output_neuron; i++)
    {
        sum = 0;
        for (int j = 0; j < nb_letter; j++)
        {
            sum += expected_output[i][j] * log(output[i][j] + epsilon) +
            (1 - expected_output[i][j]) * log(1 - output[i][j] + epsilon);
        }
    }
    
    return -((float)1 / nb_letter) * sum;
}