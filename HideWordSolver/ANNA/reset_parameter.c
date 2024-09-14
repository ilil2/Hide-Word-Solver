#include "neural_network.h"
#include <stdlib.h>
#include <time.h>

void reset_parameter(double **w_input, // input_neuron x hidden_neuron
		    double **w_output, // hidden_neuron x output_neuron
		    double *b_input, // hidden_neuron
		    double *b_output) // output_neuron
{
    
    srand(time(0));

    for (int i = 0; i < input_neuron; i++)
    {
        for (int j = 0; j < hidden_neuron; j++)
        {
            w_input[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }

    for (int i = 0; i < hidden_neuron; i++)
    {
        for (int j = 0; j < output_neuron; j++)
        {
            w_output[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        }
    }

    for (int i = 0; i < hidden_neuron; i++)
    {
        b_input[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    }

    for (int i = 0; i < output_neuron; i++)
    {
        b_output[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    }

    save_parameter(w_input, w_output, b_input, b_output);
}