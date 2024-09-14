#include "neural_network.h"

void load_parameter(double w_input[input_neuron][hidden_neuron],
		double w_output[hidden_neuron][output_neuron],
        double b_input[hidden_neuron],
        double b_output[output_neuron])
{
    FILE* file_w_input = NULL;
	FILE* file_w_output = NULL;
	FILE* file_b_input = NULL;
	FILE* file_b_output = NULL;

	file_w_input = fopen("ANNAParameter/w_input.csv", "r");
	file_w_output = fopen("ANNAParameter/w_output.csv", "r");
	file_b_input = fopen("ANNAParameter/b_input.csv", "r");
	file_b_output = fopen("ANNAParameter/b_output.csv", "r");

    if(file_w_input != NULL)
    {
        for (int i = 0; i < input_neuron; i++)
        {
            for (int j = 0; j < hidden_neuron; j++)
            {
                fscanf(file_w_input, "%lf,", &w_input[i][j]);
            }
        }
    }
    else
    {
		printf("Error opening w_input.csv files.");
    }

    if(file_w_output != NULL)
    {
        for (int i = 0; i < hidden_neuron; i++)
        {
            for (int j = 0; j < output_neuron; j++)
            {
                fscanf(file_w_output, "%lf,", &w_output[i][j]);
            }
        }
    }
    else
    {
		printf("Error opening w_output.csv files.");  
    }

    if(file_b_input != NULL)
    {
        for (size_t i = 0; i < hidden_neuron; i++)
        {
            fscanf(file_b_input, "%lf", &b_input[i]);
        }
    }
    else
    {
		printf("Error opening b_input.csv files.");  
    }

    if(file_b_output != NULL)
    {
        for (int i = 0; i < output_neuron; i++)
        {
            fscanf(file_b_output, "%lf", &b_output[i]);
        }
    }
    else
    {
		printf("Error opening b_output.csv files."); 
    }
}
