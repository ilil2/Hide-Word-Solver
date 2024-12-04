#include "neural_network.h"

Adam* init_adam(Info* info)
{
	Adam* adam = malloc(sizeof(Adam));

    if (adam == NULL)
    {
        err(1, "malloc()");
    }

    adam->m_weight = malloc(sizeof(float **) * info->nb_layer - 1);
    adam->v_weight = malloc(sizeof(float **) * info->nb_layer - 1);
    adam->m_bias = malloc(sizeof(float *) * info->nb_layer - 1);
    adam->v_bias = malloc(sizeof(float *) * info->nb_layer - 1);

    if (adam->m_weight == NULL || adam->v_weight == NULL ||
        adam->m_bias == NULL || adam->v_bias == NULL)
    {
        err(1, "malloc()");
    }

    for (size_t i = 0; i < info->nb_layer - 1; i++)
    {
        adam->m_weight[i] = malloc(sizeof(float *) * info->nb_neuron[i+1]);
        adam->v_weight[i] = malloc(sizeof(float *) * info->nb_neuron[i+1]);
        adam->m_bias[i] = calloc(info->nb_neuron[i+1], sizeof(float));
        adam->v_bias[i] = calloc(info->nb_neuron[i+1], sizeof(float));

        if (adam->m_weight[i] == NULL || adam->v_weight[i] == NULL ||
            adam->m_bias[i] == NULL || adam->v_bias[i] == NULL)
        {
            err(1, "malloc()");
        }

        for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
        {
            adam->m_weight[i][j] = calloc(info->nb_neuron[i], sizeof(float));
            adam->v_weight[i][j] = calloc(info->nb_neuron[i], sizeof(float));

            if (adam->m_weight[i][j] == NULL || adam->v_weight[i][j] == NULL)
            {
                err(1, "calloc()");
            }
        }
    }

	return adam;
}
