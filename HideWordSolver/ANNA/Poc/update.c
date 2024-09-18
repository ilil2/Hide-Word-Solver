#include "poc.h"

void update(double **w_input, // hidden_neuron x input_neuron
		double **w_output, // output_neuron x hidden_neuron
		double *b_input, // hidden_neuron
		double *b_output, // output_neuron
		double **dw_output, // output_neuron x hidden_neuron
		double *db_output, // output_neuron
		double **dw_input, // hidden_neuron x input_neuron
		double *db_input, // hidden_neuron
        double learning_rate)
{
    for (size_t i = 0; i < hidden_neuron; i++)
    {
        for (size_t j = 0; j < input_neuron; j++)
        {
            w_input[i][j] -= learning_rate * dw_input[i][j];
        }

        b_input[i] -= learning_rate * db_input[i];
    }

    for (size_t i = 0; i < output_neuron; i++)
    {
        for (size_t j = 0; j < hidden_neuron; j++)
        {
            w_output[i][j] -= learning_rate * dw_output[i][j];
        }

        b_output[i] -= learning_rate * db_output[i];
    }
}