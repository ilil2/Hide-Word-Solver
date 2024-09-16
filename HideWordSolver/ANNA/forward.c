#include "neural_network.h"

void forward(double *input,
		double *hidden,
		double *output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output)
{
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		double sum = 0;
		for (size_t j = 0; j < input_neuron; j++)
		{
			sum += input[j] * w_input[j][i];
		}
		hidden[i] = sum + b_input[i];
		hidden[i] = sigmoid(hidden[i]);
	}

	for (size_t i = 0; i < output_neuron; i++)
	{
		double sum = 0;
		for (size_t j = 0; j < hidden_neuron; j++)
		{
			sum += hidden[j] * w_output[j][i];
		}
		output[i] = sum + b_output[i];
		output[i] = sigmoid(output[i]);
	}
}
