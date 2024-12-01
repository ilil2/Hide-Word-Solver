#include "neural_network.h"

void load_image(char *file_path,
        int file_nb,
        ANNA* anna)
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

    // Load input and output data from csv file
    if (input_file != NULL && output_file != NULL)
    {
        for (size_t i = 0; i < anna->v->train_data; i++)
        {
            for (size_t j = 0; j < anna->i->nb_neuron[0]; j++)
            {
                fscanf(input_file, "%f,", &anna->p->neuron[0][j][i]);
                // Set the data between 0 and 1
                anna->p->neuron[0][j][i] /= 255.0;
            }

            for (size_t j = 0; j < anna->i->nb_neuron[anna->i->nb_layer-1]; j++)
            {
                fscanf(output_file, "%f,", &anna->p->expected_output[j][i]);
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
