#include "neural_network.h"

void save_stats(size_t i, float log_loss, float train_set, float test_set)
{
    // Save new ANNA stats
    FILE* save_file = NULL;

    save_file = fopen("ANNAStats/anna_stats.csv", "a");

    if (!save_file)
	{
        err(1, "fopen()");
    }

    fprintf(save_file, "%zu,%f,%f,%f\n", i, log_loss, train_set, test_set);

    fclose(save_file);
}