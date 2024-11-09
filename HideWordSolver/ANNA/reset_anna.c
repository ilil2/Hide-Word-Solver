#include "neural_network.h"

void reset_anna(float **w_input, // hidden_neuron1 x input_neuron
		float **w_hidden, // hidden_neuron2 x hidden_neuron1
		float **w_output, // output_neuron x hidden_neuron
		float *b_input, // hidden_neuron1
		float *b_hidden, // hidden_neuron2
		float *b_output) // output_neuron
{
    // Reset ANNA parameter
    reset_parameter(w_input, w_hidden, w_output, b_input, b_hidden, b_output);

    // Reset ANNA hyperparameter
    reset_hyperparameter();

    // Reset ANNA stats file
    FILE* save_file = NULL;

    save_file = fopen("ANNAStats/anna_stats.csv", "w");

    fprintf(save_file, "iteration,log loss,train result,test result\n");

    fclose(save_file);
}