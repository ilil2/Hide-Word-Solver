#include "neural_network.h"

void free_all(ANNA* anna)
{
    // Free parameter
    free_param(anna->p, anna->i, anna->v, 0);

    // Free adam
    free_adam(anna->a, anna->i);

    // Free other parameter
	free(anna->i->nb_neuron);
    free(anna->i);
    free(anna->hp);
    free(anna->v);
    free(anna);
}