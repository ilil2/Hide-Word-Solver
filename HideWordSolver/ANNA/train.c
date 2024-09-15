#include "neural_network.h"

void train(int letter_nb, double** syn_input, double** syn_output,
			double* b_input, double* b_output)
{
	//Memory allocations
	double*** input = malloc(sizeof(double**) * letter_nb);

	for (int i = 0; i < letter_nb; i++)
	{
		input[i] = malloc(sizeof(double*) * 1);
		input[i][0] = malloc(sizeof(double) * input_neuron);
	}

	double** hidden = malloc(sizeof(double*) * 1);
	hidden[0] = malloc(sizeof(double) * hidden_neuron);

	double** output = malloc(sizeof(double*) * 1);
	output[0] = malloc(sizeof(double) * output_neuron);

	double** real_output = malloc(sizeof(double*) * 1);
	real_output[0] = malloc(sizeof(double) * output_neuron);

	//Backward
	double** output_error = malloc(sizeof(double*) * output_neuron);
	for (size_t i = 0; i < output_neuron; i++)
	{
		output_error[i] = malloc(sizeof(double) * 1);
	}

	double** output_delta = malloc(sizeof(double*) * 1);
	output_delta[0] = malloc(sizeof(double) * output_neuron);

	double** t_syn_output = malloc(sizeof(double*) * output_neuron);
	for (size_t i = 0; i < output_neuron; i++)
	{
		t_syn_output[i] = malloc(sizeof(double) * hidden_neuron);
	}

	double** hidden_error = malloc(sizeof(double*) * 1);
	hidden_error[0] = malloc(sizeof(double) * hidden_neuron);

	double** hidden_delta = malloc(sizeof(double*) * 1);
	hidden_delta[0] = malloc(sizeof(double) * hidden_neuron);

	double** t_input = malloc(sizeof(double*) * input_neuron);
	for (size_t i = 0; i < input_neuron; i++)
	{
		t_input[i] = malloc(sizeof(double) * 1);
	}

	double** mult_syn_input = malloc(sizeof(double*) * input_neuron);
	for (size_t i = 0; i < input_neuron; i++)
	{
		mult_syn_input[i] = malloc(sizeof(double) * hidden_neuron);
	}

	double** t_hidden =  malloc(sizeof(double*) * hidden_neuron);
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		t_hidden[i] = malloc(sizeof(double) * 1);
	}

	double** mult_syn_output = malloc(sizeof(double*) * hidden_neuron);
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		mult_syn_output[i] = malloc(sizeof(double) * output_neuron);
	}

	load_parameter(syn_input, syn_output, b_input, b_output);

	unsigned long long loop = 0;
	size_t nb_while = 42;
	while (nb_while)
	{
		//nb_while -= 1;
		loop++;
		printf("Boucle numero : %llu\n", loop);

		for (char i = 'A'; i <= 'Z'; i++)
		{
			printf("\tLettre : %c\n", i);

			char path[30];
			sprintf(path, "Dataset/Train/%c.csv", i);

			load_image(path, letter_nb, input);

			convert_char_to_output(i, real_output[0]);

			for (int j = 0; j < letter_nb; j++)
			{
				forward(input[j], syn_input, hidden, syn_output, output);
				backward(input[j], syn_input, hidden, real_output, output,
						syn_output, output_error, output_delta, t_syn_output, 
						hidden_error, hidden_delta, t_input, mult_syn_input, 
						t_hidden, mult_syn_output);
			}
		}

		save_parameter(syn_input, syn_output, b_input, b_output);
		printf("\tsave ! \n");
	}

	//Memory release
	for (int i = 0; i < letter_nb; i++)
	{
		free(input[i][0]);
		free(input[i]);
	}
	free(input);

	free(hidden[0]);
	free(hidden);

	free(output[0]);
	free(output);

	free(real_output[0]);
	free(real_output);

	// Backward
	for (size_t i = 0; i < output_neuron; i++)
	{
		free(output_error[i]);
	}
	free(output_error);

	free(output_delta[0]);
	free(output_delta);

	for (size_t i = 0; i < output_neuron; i++)
	{
		free(t_syn_output[i]);
	}
	free(t_syn_output);

	free(hidden_error[0]);
	free(hidden_error);

	free(hidden_delta[0]);
	free(hidden_delta);

	for (size_t i = 0; i < input_neuron; i++)
	{
		free(t_input[i]);
	}
	free(t_input);

	for (size_t i = 0; i < input_neuron; i++)
	{
		free(mult_syn_input[i]);
	}
	free(mult_syn_input);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		free(t_hidden[i]);
	}
	free(t_hidden);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		free(mult_syn_output[i]);
	}
	free(mult_syn_output);
}
