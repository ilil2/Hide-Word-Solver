#include "neural_network.h"

void save_parameter(const double **w_input, // input_neuron x hidden_neuron
		const double **w_output, // hidden_neuron x output_neuron
		const double *b_input, // hidden_neuron
		const double *b_output) // output_neuron
{
	FILE* file_w_input = NULL;
	FILE* file_w_output = NULL;
	FILE* file_b_input = NULL;
	FILE* file_b_output = NULL;

	file_w_input = fopen("ANNAParameter/w_input.csv", "w");
	file_w_output = fopen("ANNAParameter/w_output.csv", "w");
	file_b_input = fopen("ANNAParameter/b_input.csv", "w");
	file_b_output = fopen("ANNAParameter/b_output.csv", "w");

	if (file_w_input != NULL)
	{
		for (int i = 0; i < input_neuron; i++)
		{
        	for (int j = 0; j < hidden_neuron; j++)
			{
            	fprintf(file_w_input, "%f", w_input[i][j]);

            	if (j < hidden_neuron - 1)
				{
                	fprintf(file_w_input, ",");
            	}
        	}

        	fprintf(file_w_input, "\n");
    	}
    }
	else
	{
		printf("Error opening w_input.csv files.");
	}

	fclose(file_w_input);

	if (file_w_output != NULL)
	{
		for (int i = 0; i < hidden_neuron; i++)
		{
        	for (int j = 0; j < output_neuron; j++)
			{
            	fprintf(file_w_output, "%f", w_output[i][j]);
				
            	if (j < output_neuron - 1)
				{
                	fprintf(file_w_output, ",");
            	}
        	}

        	fprintf(file_w_output, "\n");
    	}
    }
	else
	{
		printf("Error opening w_output.csv files.");
	}

	fclose(file_w_output);

	if (file_b_input != NULL)
	{
		for (size_t i = 0; i < hidden_neuron; i++)
		{
        	fprintf(file_b_input, "%f\n", b_input[i]);
    	}
    }
	else
	{
		printf("Error opening b_input.csv files.");
	}

	fclose(file_b_input);

	if (file_b_output != NULL)
	{
		for (size_t i = 0; i < output_neuron; i++)
		{
        	fprintf(file_b_output, "%f\n", b_output[i]);
    	}
    }
	else
	{
		printf("Error opening b_output.csv files.");
	}

	fclose(file_b_output);
}
