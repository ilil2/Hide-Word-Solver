#include "neural_network.h"

void load_image(char *file_path,
        int file_nb,
        size_t file_size,
        double **input, // input_neuron x file_size
        double **output) // output_neuron x file_size
{
    FILE* input_file = NULL;
    FILE* output_file = NULL;
    
    char xbuffer[50];
	char ybuffer[50];
    if (file_nb != -1)
	{
		sprintf(xbuffer, "%sx%i.csv", file_path, file_nb);
		sprintf(ybuffer, "%sy%i.csv", file_path, file_nb);
	}
	else
	{
		sprintf(xbuffer, "%sx.csv", file_path);
		sprintf(ybuffer, "%sy.csv", file_path);
	}

	input_file = fopen(xbuffer, "r");
	output_file = fopen(ybuffer, "r");

    if(input_file != NULL && output_file != NULL)
    {
        for (size_t i = 0; i < file_size; i++)
        {
            for (size_t j = 0; j < input_neuron; j++)
            {
                fscanf(input_file, "%lf,", &input[j][i]);
                input[j][i] /= 255.0;
            }

            for (size_t j = 0; j < output_neuron; j++)
            {
                fscanf(output_file, "%lf,", &output[j][i]);
            }
            
        }
    }
    else
    {
		printf("Error opening files.\n");
    }

	fclose(input_file);
	fclose(output_file);
}
