#include "neural_network.h"

void free_param(Param *param, Info *info, Var *var)
{
	if (var != NULL)
	{
		size_t i = 0;
		for (i = 0; i < info->nb_layer - 1; i++)
		{
			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				free(param->weight[i][j]);
				free(param->d_weight[i][j]);
				free(param->neuron_error[i][j]);
			}
			for (size_t j = 0; j < info->nb_neuron[i]; j++)
			{
				free(param->neuron[i][j]);
			}

			free(param->bias[i]);
			free(param->d_bias[i]);

			free(param->neuron[i]);
			free(param->neuron_error[i]);

			free(param->weight[i]);
			free(param->d_weight[i]);
		}

		free(param->weight);
		free(param->bias);
		free(param->neuron);
		free(param->d_weight);
		free(param->d_bias);
		free(param->neuron_error);

		for (size_t j = 0; j < info->nb_neuron[i]; j++)
		{
			free(param->neuron[i][j]);
		}

		free(param->neuron[i]);

		for (size_t j = 0; j < info->nb_neuron[i]; j++)
		{
			free(param->expected_output[j]);
		}

		free(param->expected_output);

		for (size_t j = 0; j < 2; j++)
		{
			free(param->result[j]);
		}

		free(param->result);
	}
	else
	{
		for (size_t i = 0; i < info->nb_layer - 1; i++)
		{
			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				free(param->weight[i][j]);
			}

			free(param->bias[i]);
			free(param->weight[i]);
		}

		free(param->weight);
		free(param->bias);
	}

	free(param);
}
