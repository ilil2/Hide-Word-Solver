#include "neural_network.h"
#include <math.h>

double log_loss(double *expected_output, double *output)
{
    double sum = 0;

    for (size_t i = 0; i < output_neuron; i++)
    {
        sum += expected_output[i] * log(output[i]) + (1 - expected_output[i]) * log(1 - output[i]);
    }
    
    return -(double)1 / output_neuron * sum;
}