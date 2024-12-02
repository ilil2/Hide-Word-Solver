#include "neural_network.h"

void update(ANNA* anna)
{
    anna->a->t += 1;
    float beta1_t = pow(anna->a->beta1, anna->a->t);
    float beta2_t = pow(anna->a->beta2, anna->a->t);

    for (size_t i = 0; i < anna->i->nb_layer - 1; i++)
    {
        for (size_t j = 0; j < anna->i->nb_neuron[i+1]; j++)
        {
            for (size_t k = 0; k < anna->i->nb_neuron[i]; k++)
            {
                anna->a->m_weight[i][j][k] = anna->a->beta1 *
                    anna->a->m_weight[i][j][k] + (1 - anna->a->beta1) *
                    anna->p->d_weight[i][j][k];
                anna->a->v_weight[i][j][k] = anna->a->beta2 *
                    anna->a->v_weight[i][j][k] + (1 - anna->a->beta2) *
                    anna->p->d_weight[i][j][k] * anna->p->d_weight[i][j][k];
                
                float m_hat = anna->a->m_weight[i][j][k] / (1 - beta1_t);
                float v_hat = anna->a->v_weight[i][j][k] / (1 - beta2_t);

                anna->p->weight[i][j][k] -= anna->hp->learning_rate *
                    (m_hat / (sqrt(v_hat) + anna->hp->espilon) +
                    anna->hp->lambda * anna->p->weight[i][j][k]);
            }

            anna->a->m_bias[i][j] = anna->a->beta1 * anna->a->m_bias[i][j] +
                (1 - anna->a->beta1) * anna->p->d_bias[i][j];
            anna->a->v_bias[i][j] = anna->a->beta2 * anna->a->v_bias[i][j] +
                (1 - anna->a->beta2) * anna->p->d_bias[i][j] *
                anna->p->d_bias[i][j];
            
            float m_hat = anna->a->m_bias[i][j] / (1 - beta1_t);
            float v_hat = anna->a->v_bias[i][j] / (1 - beta2_t);

            anna->p->bias[i][j] -= anna->hp->learning_rate * m_hat /
                (sqrt(v_hat) + anna->hp->espilon);
        }
    }
}