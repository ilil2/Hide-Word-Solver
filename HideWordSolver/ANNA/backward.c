#include "neural_network.h"

void backward(double **input, double **syn_input, double **hidden,
		double **real_output, double **output, double **syn_output,
		double** output_error, double** output_delta, double** t_syn_output,
		double** hidden_error, double** hidden_delta, double** t_input, 
		double** mult_syn_input, double** t_hidden, double** mult_syn_output)
{
	for (size_t i = 0; i < output_neuron; i++)
	{
		output_error[i][0] = real_output[0][i] - output[0][i];
		output[0][i] = sigmoid_prime(output[0][i]);
	}

	for (size_t i = 0; i < output_neuron; i++)
	{
    	output_delta[0][i] = output[0][i] * output_error[i][0];
	}

	matrix_transpose(hidden_neuron, output_neuron, syn_output, t_syn_output);

	matrix_product(1, output_neuron, output_delta,
			output_neuron, hidden_neuron, t_syn_output, hidden_error);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		hidden[0][i] = sigmoid_prime(hidden[0][i]);
	}

	for (size_t i = 0; i < hidden_neuron; i++) {
    	hidden_delta[0][i] = hidden_error[0][i] * hidden[0][i];
	}

	matrix_transpose(1, input_neuron, input, t_input);

	matrix_product(input_neuron, 1, t_input, 1, hidden_neuron,
			hidden_error, mult_syn_input);

	matrix_addition(input_neuron, hidden_neuron, mult_syn_input,
			syn_input, syn_input);

	matrix_transpose(1, hidden_neuron, hidden, t_hidden);

	matrix_product(hidden_neuron, 1, t_hidden, 1, output_neuron,
			hidden_delta, mult_syn_output);

	matrix_addition(hidden_neuron, output_neuron, mult_syn_output,
			syn_output, syn_output);
}
