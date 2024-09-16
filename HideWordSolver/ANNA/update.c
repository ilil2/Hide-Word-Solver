#include "neural_network.h"

void update(double **w_input, // input_neuron x hidden_neuron
		double **w_output, // hidden_neuron x output_neuron
		double *b_input, // hidden_neuron
		double *b_output, // output_neuron
		double **dw_output, // output_neuron x hidden_neuron
		double *db_output, // output_neuron
		double **dw_input, // input_neuron x hidden_neuron
		double *db_input, // hidden_neuron
        double learning_rate)
{
    for (size_t i = 0; i < hidden_neuron; i++)
    {
        for (size_t j = 0; j < input_neuron; j++)
        {
            w_input[j][i] = w_input[j][i] - learning_rate * dw_input[j][i];
        }

        for (size_t j = 0; j < output_neuron; j++)
        {
            w_output[j][i] = w_output[j][i] - learning_rate * dw_output[j][i];
        }

        b_input[i] = b_input[i] - learning_rate * db_input[i];
    }

    for (size_t i = 0; i < output_neuron; i++)
    {
        b_output[i] = b_output[i] - learning_rate * db_output[i];
    }
}