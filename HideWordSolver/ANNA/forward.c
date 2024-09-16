#include "neural_network.h"

void forward(double **input,
		double **syn_input,
		double **hidden,
		double **syn_output,
		double **output)
{
	for (size_t i = 0; i < input_neuron; i++)
	{
		for (size_t j = 0; j < hidden_neuron; j++)
		{
			hidden[0][j] = input[0][i] * syn_input[i][j];
		}
	}

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		hidden[0][i] = sigmoid(hidden[0][i]);
	}

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		for (size_t j = 0; j < output_neuron; j++)
		{
			output[0][j] = hidden[0][i] * syn_output[i][j];
		}
	}

	for (size_t i = 0; i < output_neuron; i++)
	{
		output[0][i] = sigmoid(output[0][i]);
	}
}
