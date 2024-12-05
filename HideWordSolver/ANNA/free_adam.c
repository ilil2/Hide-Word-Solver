#include "neural_network.h"

void free_adam(Adam* adam, Info* info)
{
    for (size_t i = 0; i < info->nb_layer - 1; i++)
    {
        if (adam->m_weight[i] != NULL)
        {
            for (size_t j = 0; j < info->nb_neuron[i + 1]; j++)
            {
                free(adam->m_weight[i][j]);
            }
            free(adam->m_weight[i]);
        }

        if (adam->v_weight[i] != NULL)
        {
            for (size_t j = 0; j < info->nb_neuron[i + 1]; j++)
            {
                free(adam->v_weight[i][j]);
            }
            free(adam->v_weight[i]);
        }

        free(adam->m_bias[i]);
        free(adam->v_bias[i]);
    }

    free(adam->m_weight);
    free(adam->v_weight);
    free(adam->m_bias);
    free(adam->v_bias);

    free(adam);
}