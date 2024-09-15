#include "neural_network.h"

char predict(double **input)
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

        double** hidden = malloc(sizeof(double*[1]));
        hidden[0] = malloc(sizeof(double[hidden_neuron]));

    	double** output = malloc(sizeof(double*[1]));
        output[0] = malloc(sizeof(double[output_neuron]));

		forward(input, syn_input, hidden, syn_output, output);
		char res = convert_output_to_char(input);

		free(input);
		free(hidden);
		free(output);

		free(syn_input);
		free(syn_output);
		free(b_input);
		free(b_output);

		return res;
}
