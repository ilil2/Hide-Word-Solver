#include "neural_network.h"

void train(int nb_letter, char *anna_result, double** w_input,
			double** w_output, double* b_input, double* b_output)
{
	//Memory allocations//

	double** input = malloc(sizeof(double*) * input_neuron);
	for (int i = 0; i < input_neuron; i++)
	{
		input[i] = malloc(sizeof(double) * nb_letter);
	}

	double** hidden = malloc(sizeof(double) * hidden_neuron);
	for (int i = 0; i < hidden_neuron; i++)
	{
		hidden[i] = malloc(sizeof(double) * nb_letter);
	}

	double** output = malloc(sizeof(double) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		output[i] = malloc(sizeof(double) * nb_letter);
	}

	double** expected_output = malloc(sizeof(double) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		expected_output[i] = malloc(sizeof(double) * nb_letter);
	}

	double** output_error = malloc(sizeof(double) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		output_error[i] = malloc(sizeof(double) * nb_letter);
	}

	double** dw_output = malloc(sizeof(double*) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		dw_output[i] = malloc(sizeof(double) * hidden_neuron);
	}

	double* db_output = malloc(sizeof(double) * output_neuron);

	double** hidden_error = malloc(sizeof(double) * hidden_neuron);
	for (int i = 0; i < hidden_neuron; i++)
	{
		hidden_error[i] = malloc(sizeof(double) * nb_letter);
	}

	double** dw_input = malloc(sizeof(double*) * hidden_neuron);
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		dw_input[i] = malloc(sizeof(double) * input_neuron);
	}

	double* db_input = malloc(sizeof(double) * hidden_neuron);

	//////////////////////

	double learning_rate = 1;
	load_parameter(w_input, w_output, b_input, b_output);

	unsigned long long loop = 0;
	size_t nb_while = 42;
	char char_list[nb_symbols] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	printf("%c\n", char_list[0]);

	while (nb_while)
	{
		//nb_while -= 1;
		loop++;
		shuffle(char_list, nb_symbols);
		printf("Boucle numero : %llu\n", loop);

		for (int i = 0; i < nb_symbols; i++)
		{
			printf("\tLettre : %c\n", char_list[i]);

			char path[30];
			sprintf(path, "Dataset/Train/%c.csv", char_list[i]);

			load_image(path, nb_letter, input);

			convert_char_to_output(i + 'A', output_neuron, nb_letter, expected_output);

			forward(nb_letter, input, hidden, output, w_input, w_output,
				b_input, b_output);

			convert_output_to_char(nb_letter, output, anna_result);
			double success = 0;
			for (int i = 0; i < nb_letter; i++)
			{
				success += anna_result[i] == i + 'A';
			}
			//printf("\t\t%f\n", success / nb_letter);
			
			printf("\t\tLog Loss = %f\n", log_loss(nb_letter, expected_output, output));

			backward(nb_letter, w_output, input, hidden, output, expected_output,
				output_error, dw_output, db_output, hidden_error,
				dw_input, db_input);
			update(w_input, w_output, b_input, b_output, dw_output,
				db_output, dw_input, db_input, learning_rate);
		}

		printf("\tsave ! \n");
		save_parameter(w_input, w_output, b_input, b_output);
	}

	//Memory release//

	for (int i = 0; i < input_neuron; i++)
	{
		free(input[i]);
	}
	free(input);

	for (int i = 0; i < hidden_neuron; i++)
	{
		free(hidden[i]);
	}
	free(hidden);

	for (int i = 0; i < output_neuron; i++)
	{
		free(output[i]);
	}
	free(output);

	for (int i = 0; i < output_neuron; i++)
	{
		free(expected_output[i]);
	}
	free(expected_output);

	for (int i = 0; i < output_neuron; i++)
	{
		free(output_error[i]);
	}
    free(output_error);

	for (int i = 0; i < output_neuron; i++)
	{
		free(dw_output[i]);
	}
	free(dw_output);

	free(db_output);

	for (int i = 0; i < hidden_neuron; i++)
	{
		free(hidden_error[i]);
	}
	free(hidden_error);

	for (size_t i = 0; i < hidden_neuron; i++)
	{
		free(dw_input[i]);
	}
	free(dw_input);

	free(db_input);

	//////////////////////
}
