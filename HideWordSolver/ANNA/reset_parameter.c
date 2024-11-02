#include "neural_network.h"

void reset_parameter(double **w_input, // hidden_neuron1 x input_neuron
		double **w_hidden, // hidden_neuron2 x hidden_neuron1
		double **w_output, // output_neuron x hidden_neuron
		double *b_input, // hidden_neuron1
		double *b_hidden, // hidden_neuron2
		double *b_output) // output_neuron
{
    srand(time(0));

    // Calculates a new random weight for the first hidden layer
    double limit_w_input = sqrt(2.0 / input_neuron);
    for (int i = 0; i < hidden_neuron1; i++)
    {
        for (int j = 0; j < input_neuron; j++)
        {
            w_input[i][j] = ((double)rand() / RAND_MAX) * 2.0
                * limit_w_input - limit_w_input;
        }
    }

    // Calculates a new random weight for the second hidden layer
    double limit_w_hidden = sqrt(2.0 / hidden_neuron1);
    for (int i = 0; i < hidden_neuron2; i++)
    {
        for (int j = 0; j < hidden_neuron1; j++)
        {
            w_hidden[i][j] = ((double)rand() / RAND_MAX) * 2.0
                * limit_w_hidden - limit_w_hidden;
        }
    }

    // Calculates a new random weight for the output
    double limit_w_output = sqrt(2.0 / hidden_neuron2);
    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < hidden_neuron2; j++)
        {
            w_output[i][j] = ((double)rand() / RAND_MAX) * 2.0
                * limit_w_output - limit_w_output;
        }
    }

    // Calculates a new random bias for the first hidden layer
    for (int i = 0; i < hidden_neuron1; i++)
    {
        b_input[i] = 0.01;
    }

    // Calculates a new random bias for the second hidden layer
    for (int i = 0; i < hidden_neuron2; i++)
    {
        b_hidden[i] = 0.01;
    }

    // Calculates a new random bias for the output
    for (int i = 0; i < output_neuron; i++)
    {
        b_output[i] = 0.01;
    }

    // Save the new parameter
    save_parameter(w_input, w_hidden, w_output, b_input, b_hidden, b_output);

    // Reset ANNA stats file
    FILE* save_file = NULL;

    save_file = fopen("ANNAStats/anna_stats.csv", "w");

    fprintf(save_file, "iteration,log loss,train result,test result\n");

    fclose(save_file);
}