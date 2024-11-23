#include "neural_network.h"

void reset_all()
{
	Info* info = malloc(sizeof(Info));
	info->nb_neuron = malloc(sizeof(size_t));

	printf("Reset layers:\n");
	printf("First layer: ");
	scanf("%zu\n", &(info->nb_neuron[0]));

	printf("Hidden layers number: ");
	scanf("%zu\n", &(info->nb_layer));
	info->nb_layer += 2;
	info->nb_neuron = realloc(info->nb_neuron, sizeof(size_t) * info->nb_layer);

	size_t i = 0;
	for (i = 1; i < info->nb_layer - 1; i++)
	{
		printf("Hidden layer %zu: ", i);
		scanf("%zu\n", &(info->nb_neuron[i]));
	}

	printf("Last layer: ");
	scanf("%zu", &(info->nb_neuron[i]));
}
