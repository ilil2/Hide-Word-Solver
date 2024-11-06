#include "poc.h"

void update(float **w_input, // hidden_neuron x input_neuron
		float **w_output, // output_neuron x hidden_neuron
		float *b_input, // hidden_neuron
		float *b_output, // output_neuron
		float **dw_output, // output_neuron x hidden_neuron
		float *db_output, // output_neuron
		float **dw_input, // hidden_neuron x input_neuron
		float *db_input, // hidden_neuron
        float learning_rate)
{
    // Update the hidden layer weight and bias
    for (size_t i = 0; i < hidden_neuron; i++)
    {
        for (size_t j = 0; j < input_neuron; j++)
        {
            w_input[i][j] -= learning_rate * dw_input[i][j];
        }

        b_input[i] -= learning_rate * db_input[i];
    }

    // Update the output weight and bias
    for (size_t i = 0; i < output_neuron; i++)
    {
        for (size_t j = 0; j < hidden_neuron; j++)
        {
            w_output[i][j] -= learning_rate * dw_output[i][j];
        }

        b_output[i] -= learning_rate * db_output[i];
    }
}