#include "neural_network.h"

void reset_hyperparameter()
{
	FILE* file_hyperparameter = NULL;

    // Reset hyperparameter
	file_hyperparameter = fopen("ANNAHyperParameter/hyperparameter.csv", "w");

	if (file_hyperparameter != NULL)
	{
        fprintf(file_hyperparameter, "%i,%.10f,%.10f,%.10f,%.10f,%.10f,%i,"
        "%i,%.10f,%.10f,%.10f,%.10f,%.10f,%.10f,%i",
        0, 0.00001, 0.001, 0.001, 0.1, INFINITY, 0, 5, 0.5, 0.5, 0.02, 0.1,
        0.9, 0.999, 0);
    }
	else
	{
		printf("Error opening hyperparameter.csv files.\n");
	}

	fclose(file_hyperparameter);
}