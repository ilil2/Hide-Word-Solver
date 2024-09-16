#include "neural_network.h"

void backward(double **w_output, // output_neuron x hidden_neuron
		double *input, // input_neuron
		double *hidden, // hidden_neuron
		double *output, // output_neuron
		double *expected_output, // output_neuron
		double *output_error, // output_neuron
		double **dw_output, // output_neuron x hidden_neuron
		double *db_output, // output_neuron
		double **t_w_output, // hidden_neuron x output_neuron
		double *hidden_error, // hidden_neuron
		double **dw_input, // input_neuron x hidden_neuron
		double *db_input) // hidden_neuron
{
	for (size_t i = 0; i < output_neuron; i++)
	{
		output_error[i] = output[i] - expected_output[i];
		for (size_t j = 0; j < hidden_neuron; j++)
		{
			dw_output[i][j] = ((double)1 / output_neuron) * output_error[i] * hidden[j];
		}
		db_output[i] = ((double)1 / output_neuron) * output_error[i];
	}

	matrix_transpose(output_neuron, hidden_neuron, w_output, t_w_output);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		double sum = 0;
		for (size_t j = 0; j < output_neuron; j++)
		{
			sum += output_error[j] * t_w_output[i][j];
		}
		hidden_error[i] = sum * hidden[i] * (1 - hidden[i]);
		
		for (size_t j = 0; j < input_neuron; j++)
		{
			dw_input[i][j] = ((double)1 / output_neuron) * hidden_error[i] * input[j];
		}
		db_input[i] = ((double)1 / output_neuron) * hidden_error[i];
	}
}