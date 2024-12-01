#include "neural_network.h"

void backward(ANNA* anna)
{
    for (size_t i = 0; i < anna->i->nb_neuron[anna->i->nb_layer - 1]; i++)
    {
        for (size_t j = 0; j < anna->v->train_data; j++)
        {
            anna->p->neuron_error[anna->i->nb_layer - 2][i][j] = 
                (anna->p->neuron[anna->i->nb_layer - 1][i][j] -
                anna->p->expected_output[i][j]) *
                activ_prime(anna->p->neuron[anna->i->nb_layer - 1][i][j]);
        }
    }

    for (size_t i = anna->i->nb_layer - 1; i > 0; i--)
    {
        matrix_product_t(anna->i->nb_neuron[i], anna->v->train_data,
            anna->p->neuron_error[i-1], anna->i->nb_neuron[i-1],
            anna->v->train_data, anna->p->neuron[i-1], anna->p->d_weight[i-1],
            1, anna->v->threads);
        
        for (size_t j = 0; j < anna->i->nb_neuron[i]; j++)
        {
            for (size_t k = 0; k < anna->i->nb_neuron[i-1]; k++)
            {
                anna->p->d_weight[i-1][j][k] /= anna->v->train_data;
            }
        }
        
        for (size_t j = 0; j < anna->i->nb_neuron[i]; j++)
        {
            float sum = 0;
            for (size_t k = 0; k < anna->v->train_data; k++)
            {
                sum += anna->p->neuron_error[i-1][j][k];
            }
            anna->p->d_bias[i-1][j] = sum / anna->v->train_data;
        }
        
        if (i > 1)
        {
            matrix_product_t(anna->i->nb_neuron[i], anna->i->nb_neuron[i-1],
            anna->p->weight[i-1], anna->i->nb_neuron[i], anna->v->train_data,
            anna->p->neuron_error[i-1], anna->p->neuron_error[i-2], 0,
            anna->v->threads);

            for (size_t j = 0; j < anna->i->nb_neuron[i-1]; j++)
            {
                for (size_t k = 0; k < anna->v->train_data; k++)
                {
                    anna->p->neuron_error[i-2][j][k] *=
                        activ_prime(anna->p->neuron[i-1][j][k]);
                }
            }
        }
    }
}