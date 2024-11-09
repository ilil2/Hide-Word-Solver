#include "neural_network.h"

void load_parameter(float **w_input, // hidden_neuron1 x input_neuron
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

    // Loads the weights of the first hidden layer
	file_w_input = fopen("ANNAParameter/w_input.csv", "r");

    if (file_w_input != NULL)
    {
        for (int i = 0; i < hidden_neuron1; i++)
        {
            for (int j = 0; j < input_neuron; j++)
            {
                fscanf(file_w_input, "%f,", &w_input[i][j]);
            }
        }
    }
    else
    {
		printf("Error opening w_input.csv files.\n");
    }

	fclose(file_w_input);

    // Loads the weights of the second hidden layer
    file_w_hidden = fopen("ANNAParameter/w_hidden.csv", "r");

    if (file_w_hidden != NULL)
    {
        for (int i = 0; i < hidden_neuron2; i++)
        {
            for (int j = 0; j < hidden_neuron1; j++)
            {
                fscanf(file_w_hidden, "%f,", &w_hidden[i][j]);
            }
        }
    }
    else
    {
		printf("Error opening w_hidden.csv files.\n");
    }

	fclose(file_w_hidden);

    // Loads the weights of the output
	file_w_output = fopen("ANNAParameter/w_output.csv", "r");

    if (file_w_output != NULL)
    {
        for (int i = 0; i < output_neuron; i++)
        {
            for (int j = 0; j < hidden_neuron2; j++)
            {
                fscanf(file_w_output, "%f,", &w_output[i][j]);
            }
        }
    }
    else
    {
		printf("Error opening w_output.csv files.\n");  
    }

	fclose(file_w_output);

    // Loads the bias of the first hidden layer
	file_b_input = fopen("ANNAParameter/b_input.csv", "r");

    if (file_b_input != NULL)
    {
        for (size_t i = 0; i < hidden_neuron1; i++)
        {
            fscanf(file_b_input, "%f", &b_input[i]);
        }
    }
    else
    {
		printf("Error opening b_input.csv files.\n");  
    }

	fclose(file_b_input);

    // Loads the bias of the second hidden layer
    file_b_hidden = fopen("ANNAParameter/b_hidden.csv", "r");

    if (file_b_hidden != NULL)
    {
        for (size_t i = 0; i < hidden_neuron2; i++)
        {
            fscanf(file_b_hidden, "%f", &b_hidden[i]);
        }
    }
    else
    {
		printf("Error opening b_hidden.csv files.\n");  
    }

	fclose(file_b_hidden);

    // Loads the bias of the output
	file_b_output = fopen("ANNAParameter/b_output.csv", "r");

    if (file_b_output != NULL)
    {
        for (int i = 0; i < output_neuron; i++)
        {
            fscanf(file_b_output, "%f", &b_output[i]);
        }
    }
    else
    {
		printf("Error opening b_output.csv files.\n"); 
    }

	fclose(file_b_output);
}
