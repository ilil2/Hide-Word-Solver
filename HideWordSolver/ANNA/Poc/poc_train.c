#include "poc.h"
#include <math.h>
#include <time.h>

int main()
{
	double **w_input = malloc(hidden_neuron * sizeof(double *));
    for (int i = 0; i < hidden_neuron; i++)
        w_input[i] = malloc(input_neuron * sizeof(double));

    double **w_output = malloc(output_neuron * sizeof(double *));
    for (int i = 0; i < output_neuron; i++)
        w_output[i] = malloc(hidden_neuron * sizeof(double));

    double *b_input = malloc(hidden_neuron * sizeof(double));

    double *b_output = malloc(output_neuron * sizeof(double));

	double limit_w_input = sqrt(6.0 / (hidden_neuron + input_neuron));
    for (int i = 0; i < hidden_neuron; i++)
    {
        for (int j = 0; j < input_neuron; j++)
        {
            w_input[i][j] = ((double)rand() / RAND_MAX) * 2.0 * limit_w_input - limit_w_input;
        }
    }

    double limit_w_output = sqrt(6.0 / (output_neuron + hidden_neuron));
    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < hidden_neuron; j++)
        {
            w_output[i][j] = ((double)rand() / RAND_MAX) * 2.0 * limit_w_output - limit_w_output;
        }
    }

    for (int i = 0; i < hidden_neuron; i++)
    {
        b_input[i] = ((double)rand() / RAND_MAX) * 2.0 - 0.01;
    }

    for (int i = 0; i < output_neuron; i++)
    {
        b_output[i] = ((double)rand() / RAND_MAX) * 2.0 - 0.01;
    }

	double** input = malloc(sizeof(double*) * input_neuron);
	for (int i = 0; i < input_neuron; i++)
	{
		input[i] = malloc(sizeof(double) * nb_letters);
	}

	input[0][0] = 0;
	input[1][0] = 0;
	input[0][1] = 0;
	input[1][1] = 1;
	input[0][2] = 1;
	input[1][2] = 0;
	input[0][3] = 1;
	input[1][3] = 1;

	double** hidden = malloc(sizeof(double) * hidden_neuron);
	for (int i = 0; i < hidden_neuron; i++)
	{
		hidden[i] = malloc(sizeof(double) * nb_letters);
	}

	double** output = malloc(sizeof(double) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		output[i] = malloc(sizeof(double) * nb_letters);
	}

	double** expected_output = malloc(sizeof(double) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		expected_output[i] = malloc(sizeof(double) * nb_letters);
	}

	expected_output[0][0] = 1;
	expected_output[0][1] = 0;
	expected_output[0][2] = 0;
	expected_output[0][3] = 1;

	double** output_error = malloc(sizeof(double) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		output_error[i] = malloc(sizeof(double) * nb_letters);
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
		hidden_error[i] = malloc(sizeof(double) * nb_letters);
	}

	double** dw_input = malloc(sizeof(double*) * hidden_neuron);
	for (size_t i = 0; i < hidden_neuron; i++)
	{
		dw_input[i] = malloc(sizeof(double) * input_neuron);
	}

	double* db_input = malloc(sizeof(double) * hidden_neuron);

	double learning_rate = 1;

	unsigned long long loop = 0;
	size_t nb_while = 250;

	while (nb_while)
	{
		nb_while -= 1;
		loop++;
		printf("Boucle numero : %llu\n", loop);

		forward(nb_letters, input, hidden, output, w_input, w_output,
				b_input, b_output);
			
		printf("\t\tLog Loss = %f\n", log_loss(nb_letters, expected_output, output));

		backward(nb_letters, w_output, input, hidden, output, expected_output,
			output_error, dw_output, db_output, hidden_error,
			dw_input, db_input);
		update(w_input, w_output, b_input, b_output, dw_output,
			db_output, dw_input, db_input, learning_rate);
		
		for (size_t i = 0; i < 4; i++)
		{
			if (output[0][i] > 0.5)
			{
				output[0][i] = 1;
			}
			else
			{
				output[0][i] = 0;
			}
			
			printf("%c, ", (output[0][i] == expected_output[0][i]) + '0');
		}
		printf("\n");
		
	}
}