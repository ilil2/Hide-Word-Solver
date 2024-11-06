#include "neural_network.h"

void save_parameter(float **w_input, // hidden_neuron1 x input_neuron
		float **w_hidden, // hidden_neuron2 x hidden_neuron1
		float **w_output, // output_neuron x hidden_neuron
		float *b_input, // hidden_neuron1
		float *b_hidden, // hidden_neuron2
		float *b_output) // output_neuron
{
	FILE* file_w_input = NULL;
	FILE* file_w_hidden = NULL;
	FILE* file_w_output = NULL;
	FILE* file_b_input = NULL;
	FILE* file_b_hidden = NULL;
	FILE* file_b_output = NULL;

    // Save the weights of the first hidden layer
	file_w_input = fopen("ANNAParameter/w_input.csv", "w");

	if (file_w_input != NULL)
	{
		for (int i = 0; i < hidden_neuron1; i++)
		{
        	for (int j = 0; j < input_neuron; j++)
			{
            	fprintf(file_w_input, "%.15f", w_input[i][j]);

            	if (j < input_neuron - 1)
				{
                	fprintf(file_w_input, ",");
            	}
        	}

        	fprintf(file_w_input, "\n");
    	}
    }
	else
	{
		printf("Error opening w_input.csv files.\n");
	}

	fclose(file_w_input);

    // Save the weights of the second hidden layer
	file_w_hidden = fopen("ANNAParameter/w_hidden.csv", "w");

	if (file_w_hidden != NULL)
	{
		for (int i = 0; i < hidden_neuron2; i++)
		{
        	for (int j = 0; j < hidden_neuron1; j++)
			{
            	fprintf(file_w_hidden, "%.15f", w_hidden[i][j]);

            	if (j < hidden_neuron1 - 1)
				{
                	fprintf(file_w_hidden, ",");
            	}
        	}

        	fprintf(file_w_hidden, "\n");
    	}
    }
	else
	{
		printf("Error opening w_hidden.csv files.\n");
	}

	fclose(file_w_hidden);

    // Save the weights of the output
	file_w_output = fopen("ANNAParameter/w_output.csv", "w");

	if (file_w_output != NULL)
	{
		for (int i = 0; i < output_neuron; i++)
		{
        	for (int j = 0; j < hidden_neuron2; j++)
			{
            	fprintf(file_w_output, "%.15f", w_output[i][j]);
				
            	if (j < hidden_neuron2 - 1)
				{
                	fprintf(file_w_output, ",");
            	}
        	}

        	fprintf(file_w_output, "\n");
    	}
    }
	else
	{
		printf("Error opening w_output.csv files.\n");
	}

	fclose(file_w_output);

    // Save the bias of the first hidden layer
	file_b_input = fopen("ANNAParameter/b_input.csv", "w");

	if (file_b_input != NULL)
	{
		for (size_t i = 0; i < hidden_neuron1; i++)
		{
        	fprintf(file_b_input, "%.15f\n", b_input[i]);
    	}
    }
	else
	{
		printf("Error opening b_input.csv files.\n");
	}

	fclose(file_b_input);

    // Save the bias of the second hidden layer
	file_b_hidden = fopen("ANNAParameter/b_hidden.csv", "w");

	if (file_b_hidden != NULL)
	{
		for (size_t i = 0; i < hidden_neuron2; i++)
		{
        	fprintf(file_b_hidden, "%.15f\n", b_hidden[i]);
    	}
    }
	else
	{
		printf("Error opening b_hidden.csv files.\n");
	}

	fclose(file_b_hidden);

    // Save the bias of the output
	file_b_output = fopen("ANNAParameter/b_output.csv", "w");

	if (file_b_output != NULL)
	{
		for (size_t i = 0; i < output_neuron; i++)
		{
        	fprintf(file_b_output, "%.15f\n", b_output[i]);
    	}
    }
	else
	{
		printf("Error opening b_output.csv files.\n");
	}

	fclose(file_b_output);
}
