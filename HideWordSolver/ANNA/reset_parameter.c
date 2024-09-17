#include "neural_network.h"
#include <math.h>
#include <time.h>

void reset_parameter(double **w_input, // hidden_neuron x input_neuron
		    double **w_output, // output_neuron x hidden_neuron
		    double *b_input, // hidden_neuron
		    double *b_output) // output_neuron
{
    srand(time(0));

    double limit_w_input = sqrt(6.0 / (hidden_neuron + input_neuron));
    for (int i = 0; i < hidden_neuron; i++)
    {
        for (int j = 0; j < input_neuron; j++)
        {
            w_input[i][j] = ((double)rand() / RAND_MAX) * 2.0 * limit_w_input - limit_w_input;
        }
    }

    double limit_w_output = sqrt(6.0 / (output_neuron + hidden_neuron));
    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < hidden_neuron; j++)
        {
            w_output[i][j] = ((double)rand() / RAND_MAX) * 2.0 * limit_w_output - limit_w_output;
        }
    }

    for (int i = 0; i < hidden_neuron; i++)
    {
        b_input[i] = ((double)rand() / RAND_MAX) * 2.0 - 0.01;
    }

    for (int i = 0; i < output_neuron; i++)
    {
        b_output[i] = ((double)rand() / RAND_MAX) * 2.0 - 0.01;
    }

    save_parameter(w_input, w_output, b_input, b_output);
}