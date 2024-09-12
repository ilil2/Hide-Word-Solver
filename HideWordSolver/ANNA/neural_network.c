#include "neural_network.h"

int main(int argc, char** argv)
{
    double w_input[input_neuron][hidden_neuron];
    double w_output[hidden_neuron][output_neuron];
    double b_input[hidden_neuron];
    double b_output[output_neuron];

    load(w_input, w_output, b_input, b_output);

    return 0;
}
