#include "neural_network.h"

Adam* init_adam(Info* info)
{
	Adam* adam = malloc(sizeof(Adam));

    adam->m_weight = malloc(sizeof(float **) * info->nb_layer - 1);
    adam->v_weight = malloc(sizeof(float **) * info->nb_layer - 1);
    adam->m_bias = malloc(sizeof(float *) * info->nb_layer - 1);
    adam->v_bias = malloc(sizeof(float *) * info->nb_layer - 1);

    for (size_t i = 0; i < info->nb_layer - 1; i++)
    {
        adam->m_weight[i] = malloc(sizeof(float *) * info->nb_neuron[i+1]);
        adam->v_weight[i] = malloc(sizeof(float *) * info->nb_neuron[i+1]);
        adam->m_bias[i] = malloc(sizeof(float) * info->nb_neuron[i+1]);
        adam->v_bias[i] = malloc(sizeof(float) * info->nb_neuron[i+1]);

        for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
        {
            adam->m_weight[i][j] = malloc(sizeof(float) * info->nb_neuron[i]);
            adam->v_weight[i][j] = malloc(sizeof(float) * info->nb_neuron[i]);
        }
    }
    

	return adam;
}