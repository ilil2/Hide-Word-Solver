#include "neural_network.h"

void predict(ANNA* anna)
{
    forward(anna);

    convert_output_to_char(anna->v->train_data,
		anna->i->nb_neuron[anna->i->nb_layer-1],
		anna->p->neuron[anna->i->nb_layer-1],
		anna->p->result[0]);
}
