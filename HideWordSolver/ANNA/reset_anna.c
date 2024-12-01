#include "neural_network.h"

void reset_anna(Param* param,
		Info* info)
{
    // Reset ANNA parameter
    reset_parameter(param, info);

    // Reset ANNA hyperparameter
    reset_hyperparameter();

    // Reset ANNA stats file
    FILE* save_file = NULL;

    save_file = fopen("ANNAStats/anna_stats.csv", "w");

    fprintf(save_file, "iteration,log loss,train result,test result\n");

    fclose(save_file);
}