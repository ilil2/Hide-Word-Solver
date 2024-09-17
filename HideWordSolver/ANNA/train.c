#include "neural_network.h"

void train(int letter_nb, double** w_input, double** w_output,
			double* b_input, double* b_output)
{
	//Memory allocations//

	double** input = malloc(sizeof(double*) * letter_nb);
	for (int i = 0; i < letter_nb; i++)
	{
		input[i] = malloc(sizeof(double) * input_neuron);
	}

	double* hidden = malloc(sizeof(double) * hidden_neuron);

	double* output = malloc(sizeof(double) * output_neuron);

	double* expected_output = malloc(sizeof(double) * output_neuron);

	double* output_error = malloc(sizeof(double) * output_neuron);

	double** dw_output = malloc(sizeof(double*) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		dw_output[i] = malloc(sizeof(double) * hidden_neuron);
	}

	double* db_output = malloc(sizeof(double) * output_neuron);

	double* hidden_error = malloc(sizeof(double) * hidden_neuron);

	double** dw_input = malloc(sizeof(double*) * input_neuron);
	for (size_t i = 0; i < input_neuron; i++)
	{
		dw_input[i] = malloc(sizeof(double) * hidden_neuron);
	}

	double* db_input = malloc(sizeof(double) * hidden_neuron);

	//////////////////////

	double learning_rate = 1;
	load_parameter(w_input, w_output, b_input, b_output);

	unsigned long long loop = 0;
	size_t nb_while = 42;
	char char_list[nb_symbols] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	shuffle(char_list, nb_symbols);
	printf("%c\n", char_list[0]);

	while (nb_while)
	{
		//nb_while -= 1;
		loop++;
		printf("Boucle numero : %llu\n", loop);

		float total = 0;
		for (int i = 0; i < nb_symbols; i++)
		{
			printf("\tLettre : %c\n", char_list[i]);

			char path[30];
			sprintf(path, "Dataset/Train/%c.csv", char_list[i]);

			load_image(path, letter_nb, input);

			convert_char_to_output(i + 'A', output_neuron, expected_output);

			char res = 0;
			for (int j = 0; j < letter_nb; j++)
			{
				forward(input[j], hidden, output, w_input, w_output,
					b_input, b_output);
				backward(w_output, input[j], hidden, output, expected_output,
					output_error, dw_output, db_output, hidden_error,
					dw_input, db_input);
				update(w_input, w_output, b_input, b_output, dw_output,
					db_output, dw_input, db_input, learning_rate);
				
				res += char_list[i] == convert_output_to_char(output);
			}
			total += res / (float)letter_nb;
			printf("\t\t%2f\n", res / (float)letter_nb);
			//printf("\t\tLog Loss = %f\n", log_loss(output, expected_output));
		}
		
		printf("\t%2f\n", total / 26);
		save_parameter(w_input, w_output, b_input, b_output);
		printf("\tsave ! \n");
	}

	//Memory release//

	for (int i = 0; i < letter_nb; i++)
	{
		free(input[i]);
	}
	free(input);

	free(hidden);

	free(output);

	free(expected_output);

    free(output_error);

	for (int i = 0; i < output_neuron; i++)
	{
		free(dw_output[i]);
	}
	free(dw_output);

	free(db_output);

	free(hidden_error);

	for (size_t i = 0; i < input_neuron; i++)
	{
		free(dw_input[i]);
	}
	free(dw_input);

	free(db_input);

	//////////////////////
}
