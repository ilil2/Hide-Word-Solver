#include "neural_network.h"

void reset_hyperparameter()
{
	FILE* file_hyperparameter = NULL;

    // Reset hyperparameter
	file_hyperparameter = fopen("ANNAHyperParameter/hyperparameter.csv", "w");

	if (file_hyperparameter != NULL)
	{
        fprintf(file_hyperparameter,
			"%i,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%i",
			0,         // epoch
			0.00001f,  // lambda
			0.01f,     // learning_rate
			0.5f,      // init_dropout_rate
			0.5f,      // dropout_rate
			0.001f,    // dropout_decay_rate
			0.1f,      // min_dropout_rate
			0.9f,      // beta1
			0.999f,    // beta2
			0);        // t
    }
	else
	{
        err(1, "fopen()");
	}

	fclose(file_hyperparameter);
}