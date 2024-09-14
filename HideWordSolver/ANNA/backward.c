#include "neural_network.h"

void backward(double **input,
		double **syn_input,
		double **hidden,
		double **real_output,
		double **output,
		double **syn_output)
{
	double output_error[output_neuron][1];

	for (size_t i = 0; i < output_neuron; i++)
	{
		output_error[i][0] = real_output[0][i] - output[0][i];
		output[0][i] = sigmoid_prime(output[0][i]);
	}

	double output_delta[1][output_neuron];
	for (size_t i = 0; i < output_neuron; i++) {
    	output_delta[0][i] = output[0][i] * output_error[i][0];
	}

	double t_syn_output[output_neuron][hidden_neuron];
	matrix_transpose(output_neuron, hidden_neuron, syn_output, t_syn_output);

	double hidden_error[1][hidden_neuron];
	matrix_product(1, output_neuron, output_delta,
			output_neuron, hidden_neuron, t_syn_output, hidden_error);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		hidden[0][i] = sigmoid_prime(hidden[0][i]);
	}

	double hidden_delta[1][hidden_neuron];
	for (size_t i = 0; i < hidden_neuron; i++) {
    	hidden_delta[0][i] = hidden_error[0][i] * hidden[0][i];
	}


	double t_input[input_neuron][1];
	matrix_transpose(1, input_neuron, input, t_input);

	double mult_syn_input[input_neuron][hidden_neuron];
	matrix_product(input_neuron, 1, t_input, 1, hidden_neuron,
			hidden_error, mult_syn_input);

	matrix_addition(input_neuron, hidden_neuron, mult_syn_input,
			syn_input, syn_input);

	double t_hidden[hidden_neuron][1];
	matrix_transpose(1, hidden_neuron, hidden, t_hidden);

	double mult_syn_output[hidden_neuron][output_neuron];
	matrix_product(hidden_neuron, 1, t_hidden, 1, output_neuron,
			hidden_delta, mult_syn_output);

	matrix_addition(hidden_neuron, output_neuron, mult_syn_output,
			syn_output, syn_output);
}
