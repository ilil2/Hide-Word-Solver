#include "neural_network.h"

void softmax(ANNA* anna)
{
	for (size_t n = 0; n < anna->v->train_data; n++)
    {
        float max = anna->p->neuron[anna->i->nb_layer-1][0][n];
        for (size_t i = 1; i < anna->i->nb_neuron[anna->i->nb_layer-1]; i++)
        {
            if (anna->p->neuron[anna->i->nb_layer-1][i][n] > max)
            {
                max = anna->p->neuron[anna->i->nb_layer-1][i][n];
            }
        }

        float sum = 0.0;
        for (size_t i = 0; i < anna->i->nb_neuron[anna->i->nb_layer-1]; i++)
        {
            anna->p->neuron[anna->i->nb_layer-1][i][n] =
                exp(anna->p->neuron[anna->i->nb_layer-1][i][n] - max);
            sum += anna->p->neuron[anna->i->nb_layer-1][i][n];
        }

        for (size_t i = 0; i < anna->i->nb_neuron[anna->i->nb_layer-1]; i++)
        {
            anna->p->neuron[anna->i->nb_layer-1][i][n] /= sum;
        }
    }
}
