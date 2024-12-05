#include "neural_network.h"

void load_hyperparameter(HyperParam* hp,
                    Adam* a,
                    Var* v)
{
	FILE* file_hyperparameter = NULL;

    // Loads the hyperparameter
	file_hyperparameter = fopen("ANNAHyperParameter/hyperparameter.csv", "r");

    if (file_hyperparameter != NULL)
    {
        fscanf(file_hyperparameter, "%zu,%f,%f,%f,%f,%f,%f,%i,%i,%f,%f,%f,%f,"
            "%f,%f,%i",
            &(v->epoch), &(hp->lambda), &(hp->init_learning_rate),
            &(hp->learning_rate), &(hp->min_learning_rate),
            &(hp->learning_decay_rate), &(hp->best_loss), &(hp->change_iteration),
            &(hp->max_change_iteration), &(hp->init_dropout_rate),
            &(hp->dropout_rate), &(hp->dropout_decay_rate),
            &(hp->min_dropout_rate), &(a->beta1), &(a->beta2), &(a->t));
        hp->espilon = 1e-6;
    }
    else
    {
        err(1, "fopen()");
    }

	fclose(file_hyperparameter);
}