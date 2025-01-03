#include "poc.h"

void forward(int nb_letter,
		float **input, // input_neuron x nb_letter
		float **hidden, // hidden_neuron x nb_letter
		float **output, // output_neuron x nb_letter
		float **w_input, // hidden_neuron x input_neuron
		float **w_output, // output_neuron x hidden_neuron
		float *b_input, // hidden_neuron
		float *b_output) // output_neuron
{
    // Apply forward propagation to neurons in the hidden layer
	matrix_product(hidden_neuron, input_neuron, w_input, input_neuron,
		nb_letter, input, hidden, 1);
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		for (int j = 0; j < nb_letter; j++)
		{
			hidden[i][j] += b_input[i];
			hidden[i][j] = sigmoid(hidden[i][j]);
		}
	}

    // Apply forward propagation to neurons in the output
	matrix_product(output_neuron, hidden_neuron, w_output, hidden_neuron,
		nb_letter, hidden, output, 1);
	for (size_t i = 0; i < output_neuron; i++)
	{
		for (int j = 0; j < nb_letter; j++)
		{
			output[i][j] += b_output[i];
			output[i][j] = sigmoid(output[i][j]);
		}
	}
}
