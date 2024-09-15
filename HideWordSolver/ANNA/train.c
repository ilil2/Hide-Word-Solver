#include "neural_network.h"

void train(int letter_nb, double** syn_input, double** syn_output,
			double* b_input, double* b_output)
{
	load_parameter(syn_input, syn_output, b_input, b_output);

	unsigned long long loop = 0;
	size_t nb_while = 10;
	while (nb_while)
	{
		nb_while -= 1;
		loop++;
		printf("Boucle numero : %llu\n", loop);

		for (char i = 'A'; i <= 'Z'; i++)
		{
			printf("\tLettre : %c\n", i);

			char path[30];
			sprintf(path, "Dataset/Train/%c.csv", i);

			double*** input = malloc(sizeof(double**) * letter_nb);

			for (int i = 0; i < letter_nb; i++)
			{
				input[i] = malloc(sizeof(double*) * 1);
				input[i][0] = malloc(sizeof(double) * input_neuron);
			}

			load_image(path, letter_nb, input);

			double** hidden = malloc(sizeof(double*) * 1);
			hidden[0] = malloc(sizeof(double) * hidden_neuron);

			double** output = malloc(sizeof(double*) * 1);
			output[0] = malloc(sizeof(double) * output_neuron);

			double** real_output = malloc(sizeof(double*) * 1);
			real_output[0] = malloc(sizeof(double) * output_neuron);
			convert_char_to_output(i, real_output[0]);

			for (int j = 0; j < letter_nb; j++)
			{
				forward(input[j], syn_input, hidden, syn_output, output);
				backward(input[j], syn_input, hidden, real_output, output,
						syn_output);
			}

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
		}
		save_parameter(syn_input, syn_output, b_input, b_output);
		printf("\tsave ! \n");
	}
}
