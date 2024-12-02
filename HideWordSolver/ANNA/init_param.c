#include "neural_network.h"

Param* init_param(Info* info, Var* var)
{
	Param* param = malloc(sizeof(Param));

	if (var != NULL)
	{
		param->weight = malloc(sizeof(float **) * (info->nb_layer - 1));
		param->bias = malloc(sizeof(float *) * (info->nb_layer - 1));
		param->neuron = malloc(sizeof(float **) * info->nb_layer);
		param->d_weight = malloc(sizeof(float **) * (info->nb_layer - 1));
		param->d_bias = malloc(sizeof(float *) * (info->nb_layer - 1));
		param->neuron_error = malloc(sizeof(float **) * (info->nb_layer - 1));

		size_t i = 0;
		for (i = 0; i < info->nb_layer - 1; i++)
		{
			param->bias[i] = malloc(info->nb_neuron[i+1] * sizeof(float));
			param->d_bias[i] = malloc(info->nb_neuron[i+1] * sizeof(float));

			param->neuron[i] = malloc(info->nb_neuron[i] * sizeof(float *));
			param->neuron_error[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));

			param->weight[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));
			param->d_weight[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));
			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				param->weight[i][j] = malloc(info->nb_neuron[i] * sizeof(float));
				param->d_weight[i][j] = malloc(info->nb_neuron[i] * sizeof(float));
				param->neuron_error[i][j] = malloc(var->train_data *
						sizeof(float));
			}
			for (size_t j = 0; j < info->nb_neuron[i]; j++)
			{
				param->neuron[i][j] = malloc(var->train_data * sizeof(float));
			}
		}

		param->neuron[i] = malloc(info->nb_neuron[i] * sizeof(float *));

		for (size_t j = 0; j < info->nb_neuron[i]; j++)
		{
			param->neuron[i][j] = malloc(var->train_data * sizeof(float));
		}

		param->expected_output = malloc(sizeof(float *) * info->nb_neuron[i]);

		for (size_t j = 0; j < info->nb_neuron[i]; j++)
		{
			param->expected_output[j] = malloc(sizeof(float) * var->train_data);
		}

		param->result = malloc(sizeof(float *) * 2);
		for (size_t j = 0; j < 2; j++)
		{
			param->result[j] = malloc(sizeof(float) * var->train_data);
		}
	}
	else
	{
		param->weight = malloc(sizeof(float **) * (info->nb_layer - 1));
		param->bias = malloc(sizeof(float *) * (info->nb_layer - 1));

		for (size_t i = 0; i < info->nb_layer - 1; i++)
		{
			param->bias[i] = malloc(info->nb_neuron[i+1] * sizeof(float));
			param->weight[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));
			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				param->weight[i][j] = malloc(info->nb_neuron[i] * sizeof(float));
			}
		}
	}

	return param;
}
