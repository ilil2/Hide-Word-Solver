#include "poc.h"

void backward(int nb_letter,
		float **w_output, // output_neuron x hidden_neuron
		float **input, // input_neuron x nb_letter
		float **hidden, // hidden_neuron x nb_letter
		float **output, // output_neuron x nb_letter
		float **expected_output, // output_neuron x nb_letter
		float **output_error, // output_neuron x nb_letter
		float **dw_output, // output_neuron x hidden_neuron
		float *db_output, // output_neuron
		float **hidden_error, // hidden_neuron x nb_letter
		float **dw_input, // hidden_neuron x input_neuron
		float *db_input) // hidden_neuron
{
    // Apply back propagation on weights and biases between output and hidden layer
	for (size_t i = 0; i < output_neuron; i++)
	{
		for (int j = 0; j < nb_letter; j++)
		{
			output_error[i][j] = output[i][j] - expected_output[i][j];
		}
	}

	matrix_product_t(output_neuron, nb_letter, output_error, hidden_neuron,
		nb_letter, hidden, dw_output, 1, 1);

	for (size_t i = 0; i < output_neuron; i++)
	{
		for (size_t j = 0; j < hidden_neuron; j++)
		{
			dw_output[i][j] = ((float)1 / nb_letter) * dw_output[i][j];
		}
	}

	for (size_t i = 0; i < output_neuron; i++)
	{
		float sum = 0;
		for (int j = 0; j < nb_letter; j++)
		{
			sum += output_error[i][j];
		}
		
		db_output[i] = ((float)1 / nb_letter) * sum;
	}

	matrix_product_t(output_neuron, hidden_neuron, w_output, output_neuron,
		nb_letter, output_error, hidden_error, 0, 1);

    // Apply back propagation on weights and biases between hidden layer and output
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		for (int j = 0; j < nb_letter; j++)
		{
			hidden_error[i][j] = hidden_error[i][j] * hidden[i][j]
				* (1 - hidden[i][j]);
		}
	}

	matrix_product_t(hidden_neuron, nb_letter, hidden_error, input_neuron,
		nb_letter, input, dw_input, 1, 1);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		for (size_t j = 0; j < input_neuron; j++)
		{
			dw_input[i][j] = ((float)1 / nb_letter) * dw_input[i][j];
		}
	}

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		float sum = 0;
		for (int j = 0; j < nb_letter; j++)
		{
			sum += hidden_error[i][j];
		}
		
		db_input[i] = ((float)1 / nb_letter) * sum;
	}
}