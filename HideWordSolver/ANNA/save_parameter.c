#include "neural_network.h"

void save_parameter(Param* param,
		Info* info)
{
	FILE* w_file = NULL;
	FILE* b_file = NULL;
	for (size_t i = 0; i < info->nb_layer - 1; i++)
	{
		char w_buffer[50];
		snprintf(w_buffer, sizeof(w_buffer), "ANNAParameter/w_%zu.csv", i);
		w_file = fopen(w_buffer, "w");

		if (w_file == NULL)
		{
			create_file(w_buffer);
			w_file = fopen(w_buffer, "w");
		}

		if (w_file != NULL)
		{
			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				for (size_t k = 0; k < info->nb_neuron[i]; k++)
				{
					fprintf(w_file, "%.15f", param->weight[i][j][k]);

					if (k < info->nb_neuron[i] - 1)
					{
						fprintf(w_file, ",");
					}
				}
        		fprintf(w_file, "\n");
			}
		}
		else
		{
			err(1, "fopen()");
		}

		fclose(w_file);

		char b_buffer[50];
		snprintf(b_buffer, sizeof(b_buffer), "ANNAParameter/b_%zu.csv", i);
		b_file = fopen(b_buffer, "w");

		if (b_file == NULL)
		{
			create_file(b_buffer);
			b_file = fopen(b_buffer, "w");
		}

		if (b_file != NULL)
		{
			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				fprintf(b_file, "%.15f\n", param->bias[i][j]);
			}
		}
		else
		{
			err(1, "fopen()");
		}

		fclose(b_file);
	}

	FILE* file_parameter = NULL;

	file_parameter = fopen("ANNAParameter/parameter.csv", "w");

	if (file_parameter != NULL)
	{
		fprintf(file_parameter, "%zu,", info->nb_layer);
		for (size_t i = 0; i < info->nb_layer; i++)
		{
			fprintf(file_parameter, "%zu", info->nb_neuron[i]);
			if (i < info->nb_layer - 1)
			{
				fprintf(file_parameter, ",");
			}
		}
	}
	else
	{
		printf("Error opening parameter.csv files.\n");
	}

	fclose(file_parameter);
}
