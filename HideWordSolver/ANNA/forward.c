#include "neural_network.h"

void forward(double **input,
		double **syn_input,
		double **hidden,
		double **syn_output,
		double **output)
{
	matrix_product(1, input_neuron, input, input_neuron, hidden_neuron,
			syn_input, hidden);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		hidden[0][i] = sigmoid(hidden[0][i]);
	}

	matrix_product(1, hidden_neuron, hidden, hidden_neuron, output_neuron,
			syn_output, output);

	for (size_t i = 0; i < output_neuron; i++)
	{
		output[0][i] = sigmoid(output[0][i]);
	}
}
