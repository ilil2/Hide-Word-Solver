#include "neural_network.h"

void backward(int nb_letter,
		double **w_output, // output_neuron x hidden_neuron
		double **input, // input_neuron x nb_letter
		double **hidden, // hidden_neuron x nb_letter
		double **output, // output_neuron x nb_letter
		double **expected_output, // output_neuron x nb_letter
		double **output_error, // output_neuron x nb_letter
		double **dw_output, // output_neuron x hidden_neuron
		double *db_output, // output_neuron
		double **hidden_error, // hidden_neuron x nb_letter
		double **dw_input, // hidden_neuron x input_neuron
		double *db_input) // hidden_neuron
{
	for (size_t i = 0; i < output_neuron; i++)
	{
		for (int j = 0; j < nb_letter; j++)
		{
			output_error[i][j] = output[i][j] - expected_output[i][j];
		}
	}

	matrix_product_t(output_neuron, nb_letter, output_error, hidden_neuron, nb_letter, hidden, dw_output, 1, 1);

	for (size_t i = 0; i < output_neuron; i++)
	{
		for (size_t j = 0; j < hidden_neuron; j++)
		{
			dw_output[i][j] = ((double)1 / nb_letter) * dw_output[i][j];
		}
	}

	for (size_t i = 0; i < output_neuron; i++)
	{
		double sum = 0;
		for (int j = 0; j < nb_letter; j++)
		{
			sum += output_error[i][j];
		}
		
		db_output[i] = ((double)1 / nb_letter) * sum;
	}

	matrix_product_t(output_neuron, hidden_neuron, w_output, output_neuron, nb_letter, output_error, hidden_error, 0, 1);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		for (int j = 0; j < nb_letter; j++)
		{
			hidden_error[i][j] = hidden_error[i][j] * hidden[i][j] * (1 - hidden[i][j]);
		}
	}

	matrix_product_t(hidden_neuron, nb_letter, hidden_error, input_neuron, nb_letter, input, dw_input, 1, 1);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		for (size_t j = 0; j < input_neuron; j++)
		{
			dw_input[i][j] = ((double)1 / nb_letter) * dw_input[i][j];
		}
	}

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		double sum = 0;
		for (int j = 0; j < nb_letter; j++)
		{
			sum += hidden_error[i][j];
		}
		
		db_input[i] = ((double)1 / nb_letter) * sum;
	}
}