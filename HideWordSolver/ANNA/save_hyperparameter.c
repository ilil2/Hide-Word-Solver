#include "neural_network.h"

void save_hyperparameter(ANNA* anna)
{
	FILE* file_hyperparameter = NULL;

    // Save the hyperparameter
	file_hyperparameter = fopen("ANNAHyperParameter/hyperparameter.csv", "w");

	if (file_hyperparameter != NULL)
	{
        fprintf(file_hyperparameter, "%zu,%.10f,%.10f,%.10f,%.10f,%.10f,%i,"
        "%i,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%i",
        anna->v->epoch, anna->hp->lambda, anna->hp->init_learning_rate,
        anna->hp->learning_rate, anna->hp->learning_decay_rate,
        anna->hp->best_loss, anna->hp->change_iteration,
        anna->hp->max_change_iteration, anna->hp->init_dropout_rate,
        anna->hp->dropout_rate, anna->hp->dropout_decay_rate,
        anna->hp->min_dropout_rate, anna->a->beta1, anna->a->beta2,
        anna->a->t);
    }
	else
	{
		printf("Error opening hyperparameter.csv files.\n");
	}

	fclose(file_hyperparameter);
}