#include "poc.h"

float log_loss(int nb_letter,
                float **expected_output, // output_neuron x nb_letter
                float **output) // output_neuron x nb_letter
{
    float sum = 0;
    float epsilon = 1e-15;
    for (size_t i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            sum += expected_output[i][j] * log(output[i][j] + epsilon) +
            (1 - expected_output[i][j]) * log(1 - output[i][j] + epsilon);
        }
    }
    
    return -((float)1 / nb_letter) * sum;
}