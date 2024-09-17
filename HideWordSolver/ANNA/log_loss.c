#include "neural_network.h"
#include <math.h>

double log_loss(double *expected_output, double *output)
{
    double sum = 0;
    double epsilon = 1e-15;

    for (size_t i = 0; i < output_neuron; i++)
    {
        double y_pred = fmin(fmax(output[i], epsilon), 1 - epsilon);
        
        sum += expected_output[i] * log(y_pred) + (1 - expected_output[i]) * log(1 - y_pred);
    }
    
    return -((double)1 / output_neuron) * sum;
}