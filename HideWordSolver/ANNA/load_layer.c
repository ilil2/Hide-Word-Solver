#include "neural_network.h"

void load_layer(Info* info)
{
    FILE* file_layerinfo = NULL;

    // Loads the layer information
	file_layerinfo = fopen("ANNAParameter/parameter.csv", "r");

    if (file_layerinfo != NULL)
    {
        fscanf(file_layerinfo, "%zu,", &(info->nb_layer));
        info->nb_neuron = malloc(sizeof(size_t) * info->nb_layer);

        for (size_t i = 0; i < info->nb_layer; i++)
        {
            fscanf(file_layerinfo, "%zu,", &(info->nb_neuron[i]));
        }
    }
    else
    {
		err(1, "fopen()");
    }

	fclose(file_layerinfo);
}