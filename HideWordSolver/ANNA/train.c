#include "neural_network.h"

void train()
{
	double** syn_input = malloc(sizeof(double*[input_neuron]));
	double** syn_output = malloc(sizeof(double*[hidden_neuron]));

	for (size_t i = 0; i < input_neuron; i++)
	{
		syn_input[i] = malloc(sizeof(double[hidden_neuron]));
	}

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		syn_output[i] = malloc(sizeof(double[output_neuron]));
	}

	double* b_input = malloc(sizeof(double[hidden_neuron]));
	double* b_output = malloc(sizeof(double[output_neuron]));

	load_parameter(syn_input, syn_output, b_input, b_output);

	unsigned long long loop = 0;
	while (42)
	{
		loop++;
		printf("Boucle numero : %llu\n", loop);

		for (char i = 'A'; i <= 'Z'; i++)
		{
			printf("\tLettre : %c\n", i);

			char path[10];
			fprintf(path, "%c.csv", i);

			double*** input = malloc(sizeof(double**[1]));
			input[0] = malloc(sizeof(double*[1]));
			input[0][0] = malloc(sizeof(double[input_neuron]));

			load_image(path, 1000, input);

			double** hidden = malloc(sizeof(double*[1]));
			hidden[0] = malloc(sizeof(double[hidden_neuron]));

			double** output = malloc(sizeof(double*[1]));
			output[0] = malloc(sizeof(double[output_neuron]));

			double** real_output = malloc(sizeof(double*[1]));
			real_output[0] = malloc(sizeof(double[output_neuron]));
			convert_char_to_output(i, real_output[0]);

			for (size_t j = 0; j < size; j++)
			{
				forward(input[j], syn_input, hidden, syn_output, output);
				backward(input[j], syn_input, hidden, real_output, output,
						syn_output);
			}

			free(input);
			free(hidden);
			free(output);
		}
		save_parapeter(syn_input, syn_output, b_input, b_output);
		printf("\tsave ! ");
	}
}
