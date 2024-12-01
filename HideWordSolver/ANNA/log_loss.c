#include "neural_network.h"

float log_loss(ANNA* anna)
{
    float sum = 0.0f;
    size_t output_layer = anna->i->nb_layer - 1;
    size_t output_neurons = anna->i->nb_neuron[output_layer];
    size_t batch_size = anna->v->train_data;

    for (size_t n = 0; n < batch_size; n++)
    {
        for (size_t i = 0; i < output_neurons; i++)
        {
            float predicted = anna->p->neuron[output_layer][i][n];
            float expected = anna->p->expected_output[i][n];

            sum += -expected * logf(predicted + anna->hp->espilon);
        }
    }

    return sum / batch_size;
}