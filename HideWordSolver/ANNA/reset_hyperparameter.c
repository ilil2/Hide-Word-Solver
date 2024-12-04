#include "neural_network.h"

void reset_hyperparameter()
{
	FILE* file_hyperparameter = NULL;

    // Reset hyperparameter
	file_hyperparameter = fopen("ANNAHyperParameter/hyperparameter.csv", "w");

	if (file_hyperparameter != NULL)
	{
        fprintf(file_hyperparameter,
			"%i,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%i,%i,%.10f,%.10f,%.10f,%.10f,"
			"%.10f,%.10f,%i",
			0,         // epoch
			0.00001f,  // lambda
			0.01f,     // init_learning_rate
			0.01f,     // learning_rate
			0.000001f, // min_learning_rate
			0.1f,      // learning_decay_rate
			100.0f,    // best_loss
			0,         // change_iteration
			5,         // max_change_iteration
			0.5f,      // init_dropout_rate
			0.5f,      // dropout_rate
			0.01f,     // dropout_decay_rate
			0.1f,      // min_dropout_rate
			0.9f,      // beta1
			0.999f,    // beta2
			0);        // t
    }
	else
	{
		printf("Error opening hyperparameter.csv files.\n");
	}

	fclose(file_hyperparameter);
}