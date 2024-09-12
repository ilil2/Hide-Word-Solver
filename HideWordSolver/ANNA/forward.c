#include "neural_network.h"
#include <stddef.h>

void forward(double input[1][input_neuron],
		double syn_input[input_neuron][hidden_neuron],
		double syn_output[hidden_neuron][output_neuron],
		double output[output_neuron][1])
{
	double hidden[1][hidden_neuron];
	matrix_product(1, input_neuron, input, input_neuron, hidden_neuron,
			syn_input, hidden);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		hidden[1][i] = sigmoid(hidden[1][i]);
	}

	double output[output_neuron][1];
	matrix_product(1, hidden_neuron, hidden, hidden_neuron, output_neuron,
			syn_output, output);

	for (size_t i = 0; i < output_neuron; i++)
	{
		output[1][i] = sigmoid(output[1][i]);
	}
}
