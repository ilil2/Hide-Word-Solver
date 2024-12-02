#include "neural_network.h"

void forward(ANNA* anna)
{
    size_t nb_layers = anna->i->nb_layer;
    size_t nb_letter = anna->v->train_data;

    for (size_t i = 0; i < nb_layers - 1; i++)
    {
        size_t current_layer_size = anna->i->nb_neuron[i];
        size_t next_layer_size = anna->i->nb_neuron[i+1];

        matrix_product(next_layer_size, current_layer_size, anna->p->weight[i],
            current_layer_size, nb_letter, anna->p->neuron[i],
            anna->p->neuron[i+1], anna->v->threads);

        for (size_t j = 0; j < next_layer_size; j++)
        {
            for (size_t k = 0; k < nb_letter; k++)
            {
                anna->p->neuron[i+1][j][k] += anna->p->bias[i][j];

                if (i != nb_layers - 2)
                {
                    anna->p->neuron[i+1][j][k] = activ(anna->p->neuron[i+1][j][k]);
                    if (anna->hp->dropout_rate > 0)
                    {
                        if ((float)rand() / RAND_MAX < anna->hp->dropout_rate)
                        {
                            anna->p->neuron[i+1][j][k] = 0;
                        }
                        else
                        {
                            anna->p->neuron[i+1][j][k] /= (1 - anna->hp->dropout_rate);
                        }
                    }
                }
            }
        }
    }

    softmax(anna);
}
