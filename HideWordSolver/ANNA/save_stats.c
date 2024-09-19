#include "neural_network.h"

void save_stats(size_t i, double log_loss, double train_set, double test_set)
{
    FILE* save_file = NULL;

    save_file = fopen("ANNAStats/anna_stats.csv", "a");

    if (!save_file)
	{
		errx(404, "Error opening ANNAStats/anna_stats.csv files.");
    }

    fprintf(save_file, "%zu,%f,%f,%f", i, log_loss, train_set, test_set);

    fclose(save_file);
}