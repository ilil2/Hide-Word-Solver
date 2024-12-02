#include "neural_network.h"

Param* init_param(Info* info, Var* var)
{
	Param* param = malloc(sizeof(Param));

	if (param == NULL)
	{
		err(1, "malloc()");
	}

	if (var != NULL)
	{
		param->weight = malloc(sizeof(float **) * (info->nb_layer - 1));
		param->bias = malloc(sizeof(float *) * (info->nb_layer - 1));
		param->neuron = malloc(sizeof(float **) * info->nb_layer);
		param->d_weight = malloc(sizeof(float **) * (info->nb_layer - 1));
		param->d_bias = malloc(sizeof(float *) * (info->nb_layer - 1));
		param->neuron_error = malloc(sizeof(float **) * (info->nb_layer - 1));

		if (param->weight == NULL || param->bias == NULL ||
			param->neuron == NULL || param->d_weight == NULL ||
			param->d_bias == NULL || param->neuron_error == NULL)
		{
			err(1, "malloc()");
		}

		size_t i = 0;
		for (i = 0; i < info->nb_layer - 1; i++)
		{
			param->bias[i] = malloc(info->nb_neuron[i+1] * sizeof(float));
			param->d_bias[i] = malloc(info->nb_neuron[i+1] * sizeof(float));

			param->neuron[i] = malloc(info->nb_neuron[i] * sizeof(float *));
			param->neuron_error[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));

			param->weight[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));
			param->d_weight[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));

			if (param->bias[i] == NULL || param->d_bias[i] == NULL ||
				param->neuron[i] == NULL || param->neuron_error[i] == NULL ||
				param->weight[i] == NULL || param->d_weight[i] == NULL)
			{
				err(1, "malloc()");
			}

			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				param->weight[i][j] = malloc(info->nb_neuron[i] * sizeof(float));
				param->d_weight[i][j] = malloc(info->nb_neuron[i] * sizeof(float));
				param->neuron_error[i][j] = malloc(var->train_data *
						sizeof(float));

				if (param->weight[i][j] == NULL || param->d_weight[i][j] == NULL ||
					param->neuron_error[i][j] == NULL)
				{
					err(1, "malloc()");
				}
			}
			for (size_t j = 0; j < info->nb_neuron[i]; j++)
			{
				param->neuron[i][j] = malloc(var->train_data * sizeof(float));

				if (param->neuron[i][j] == NULL)
				{
					err(1, "malloc()");
				}
			}
		}

		param->neuron[i] = malloc(info->nb_neuron[i] * sizeof(float *));

		if (param->neuron[i] == NULL)
		{
			err(1, "malloc()");
		}

		for (size_t j = 0; j < info->nb_neuron[i]; j++)
		{
			param->neuron[i][j] = malloc(var->train_data * sizeof(float));

			if (param->neuron[i][j] == NULL)
			{
				err(1, "malloc()");
			}
		}

		param->expected_output = malloc(sizeof(float *) * info->nb_neuron[i]);

		if (param->expected_output == NULL)
		{
			err(1, "malloc()");
		}

		for (size_t j = 0; j < info->nb_neuron[i]; j++)
		{
			param->expected_output[j] = malloc(sizeof(float) * var->train_data);

			if (param->expected_output[j] == NULL)
			{
				err(1, "malloc()");
			}
		}

		param->result = malloc(sizeof(float *) * 2);

		if (param->result == NULL)
		{
			err(1, "malloc()");
		}
	
		for (size_t j = 0; j < 2; j++)
		{
			param->result[j] = malloc(sizeof(float) * var->train_data);

			if (param->result[j] == NULL)
			{
				err(1, "malloc()");
			}
		}
	}
	else
	{
		param->weight = malloc(sizeof(float **) * (info->nb_layer - 1));
		param->bias = malloc(sizeof(float *) * (info->nb_layer - 1));

		if (param->weight == NULL || param->bias == NULL)
		{
			err(1, "malloc()");
		}

		for (size_t i = 0; i < info->nb_layer - 1; i++)
		{
			param->bias[i] = malloc(info->nb_neuron[i+1] * sizeof(float));
			param->weight[i] = malloc(info->nb_neuron[i+1] * sizeof(float *));

			if (param->weight[i] == NULL || param->bias[i] == NULL)
			{
				err(1, "malloc()");
			}

			for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
			{
				param->weight[i][j] = malloc(info->nb_neuron[i] * sizeof(float));

				if (param->weight[i][j] == NULL)
				{
					err(1, "malloc()");
				}
			}
		}
	}

	return param;
}
