#include "neural_network.h"

void load_parameter(Param* param,
		Info* info)
{
    FILE* w_file = NULL;
    FILE* b_file = NULL;

    for (size_t i = 0; i < info->nb_layer - 1; i++)
    {
        char w_buffer[50];
		snprintf(w_buffer, sizeof(w_buffer), "ANNAParameter/w_%zu.csv", i);
		w_file = fopen(w_buffer, "r");

        if (w_file != NULL)
        {
            for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				for (size_t k = 0; k < info->nb_neuron[i]; k++)
				{
                    fscanf(w_file, "%f,", &(param->weight[i][j][k]));
				}
			}
        }
        else
        {
            err(1, "fopen()");
        }

        fclose(w_file);

        char b_buffer[50];
		snprintf(b_buffer, sizeof(b_buffer), "ANNAParameter/b_%zu.csv", i);
		b_file = fopen(b_buffer, "r");

        if (b_file != NULL)
        {
            for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				fscanf(b_file, "%f", &(param->bias[i][j]));
			}
        }
        else
        {
            err(1, "fopen()");
        }
        
        fclose(b_file);
    }
}
