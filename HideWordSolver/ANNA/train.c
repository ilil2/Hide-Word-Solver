#include "neural_network.h"

void train(int nb_letter, char *anna_result, double** w_input,
			double** w_output, double* b_input, double* b_output,
			char threads)
{
	if(nb_letter > 9750)
	{
		nb_letter = 9750;
	}

	size_t test_size = 18772;

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

	double** test_input = malloc(sizeof(double) * input_neuron);
	for (size_t i = 0; i < input_neuron; i++)
	{
		test_input[i] = malloc(sizeof(double) * test_size);
	}

	double** test_hidden = malloc(sizeof(double) * hidden_neuron);
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		test_hidden[i] = malloc(sizeof(double) * test_size);
	}

	double** test_output = malloc(sizeof(double) * output_neuron);
	double** test_expected = malloc(sizeof(double) * output_neuron);
	for (size_t i = 0; i < output_neuron; i++)
	{
		test_output[i] = malloc(sizeof(double) * test_size);
		test_expected[i] = malloc(sizeof(double) * test_size);
	}

	char* anna_expected_result = malloc(nb_letter * sizeof(char));

	//////////////////////

	char dataset_order[nb_dataset];

	for (int i = 0; i < nb_dataset; i++)
	{
		dataset_order[i] = i;
	}

	shuffle(dataset_order, nb_dataset);

	double learning_rate = 1;
	load_parameter(w_input, w_output, b_input, b_output);

	unsigned long long loop = 0;
	size_t nb_while = 42;

	while (nb_while)
	{
		//nb_while -= 1;
		loop++;
		printf("Boucle numero : %llu\n", loop);

		double train_success_t = 0;
		double log_loss_t = 0;

		for (int i = 0; i < nb_dataset; i++)
		{
			printf("\t%i, Data Set %i :\n", i, dataset_order[i]);
			load_image("Dataset/Train/", dataset_order[i], nb_letter, input, expected_output);

			//matrix_shuffle(input, expected_output, output_neuron, nb_letter);

			forward(nb_letter, input, hidden, output, w_input, w_output,
				b_input, b_output, threads);

			convert_output_to_char(nb_letter, output, anna_result);
			convert_output_to_char(nb_letter, expected_output, anna_expected_result);
			double success = 0;
			for (int i = 0; i < nb_letter; i++)
			{
				if (anna_result[i] == anna_expected_result[i])
				{
					success += 1;
				}
			}
			double _log_loss = log_loss(nb_letter, expected_output, output);
			train_success_t += success / nb_letter;
			log_loss_t += _log_loss;

			printf("\t\tSuccess (%i) = %f\n", i, success / nb_letter);
			printf("\t\tLog Loss (%i) = %f\n", i, _log_loss);

			backward(nb_letter, w_output, input, hidden, output,
					expected_output, output_error, dw_output,
					db_output, hidden_error, dw_input, db_input, threads);
			update(w_input, w_output, b_input, b_output, dw_output,
				db_output, dw_input, db_input, learning_rate);
		}
		printf("\n");

		if (nb_while % 1 == 0)
		{
			printf("\tTotal log loss = %f\n", log_loss_t / nb_dataset);
			printf("\tTotal train success = %f\n", train_success_t / nb_dataset);
			double test_succes_t = test(test_size, test_input, test_hidden, test_expected, test_output, w_input,
					w_output, b_input, b_output, threads);
			save_stats(loop, log_loss_t / nb_dataset, train_success_t / nb_dataset, test_succes_t);
		}

		save_parameter(w_input, w_output, b_input, b_output);
		printf("\tSave ! \n\n");
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
