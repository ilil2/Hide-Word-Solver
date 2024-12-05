#include "neural_network.h"

void load_image(char *file_path,
        ANNA* anna)
{
    FILE* image_file = NULL;

    image_file = fopen(file_path, "r");

    if (image_file != NULL)
    {
        for (size_t i = 0; i < anna->v->train_data; i++)
        {
            for (size_t j = 0; j < anna->i->nb_neuron[0]; j++)
            {
                fscanf(image_file, "%f,", &anna->p->neuron[0][j][i]);
                // Set the data between 0 and 1
                anna->p->neuron[0][j][i] /= 255.0;
            }
        }
    }
    else
    {
        err(1, "fopen()");
    }

    fclose(image_file);
}