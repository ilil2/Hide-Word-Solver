#include "neural_network.h"
#include <err.h>

int main(int argc, char** argv)
{
    double w_input[input_neuron][hidden_neuron];
    double w_output[hidden_neuron][output_neuron];
    double b_input[hidden_neuron];
    double b_output[output_neuron];

    if(argc > 1)
    {
        if (argv[1][0] == '2')
        {
            printf("Resetting ANNA parameters...");
            reset_parameter(w_input, w_output, b_input, b_output);
            printf("ANNA's parameters have been reset.");
        }
        else if (argv[1][0] == '1')
        {
            printf("ANNA's character recognition activated !");
        }
        else
        {
            printf("ANNA's training start.");
        }
    }
    else
    {
        errx(400, "The number of arguments is invalid.");
    }

    return 0;
}
