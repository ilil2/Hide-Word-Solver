#include "neural_network.h"

void reset_parameter(Param* param,
		Info* info)
{
    for (size_t i = 0; i < info->nb_layer - 1; i++)
    {
        // Calculates a new random weight for all layer
        float w_limit = sqrt(6.0f / info->nb_neuron[i]);
        for (size_t j = 0; j < info->nb_neuron[i+1]; j++)
        {
            // Calculates a new random weight for all layer
            for (size_t k = 0; k < info->nb_neuron[i]; k++)
            {
                param->weight[i][j][k] = ((float)rand() / RAND_MAX) * 2.0f
                    * w_limit - w_limit;
            }
            // Calculates a new random bias for all layer
            param->bias[i][j] = 0.01;
        }
    }

    // Save the new parameter
    save_parameter(param, info);
}