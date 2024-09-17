#include "neural_network.h"
#include <err.h>

int main(int argc, char** argv)
{
    double **w_input = malloc(hidden_neuron * sizeof(double *));
    for (int i = 0; i < hidden_neuron; i++)
        w_input[i] = malloc(input_neuron * sizeof(double));

    double **w_output = malloc(output_neuron * sizeof(double *));
    for (int i = 0; i < output_neuron; i++)
        w_output[i] = malloc(hidden_neuron * sizeof(double));

    double *b_input = malloc(hidden_neuron * sizeof(double));

    double *b_output = malloc(output_neuron * sizeof(double));

    if(argc > 1)
    {
        if (strcomp(argv[1], "reset"))
        {
            printf("Resetting ANNA parameters...\n");

            reset_parameter(w_input, w_output, b_input, b_output);

            printf("ANNA's parameters have been reset.\n");
        }
        else if (strcomp(argv[1], "start"))
        {
            //char *anna_result = malloc(1 * sizeof(char));
            printf("ANNA's character recognition activated !\n");
        }
        else if (strcomp(argv[1], "train"))
        {
            if (argc > 2)
            {
                int nb_letter = atoi(argv[2]);
                char *anna_result = malloc(nb_letter * sizeof(char));
                printf("ANNA's training start.\n");

                train(nb_letter, anna_result, w_input, w_output, b_input, b_output);
            }
            else
            {
                errx(10, "The number of images to be taken has not been indicated.");
            }
        }
        else
        {
            errx(10, "Incorrect argument");
        }
    }
    else
    {
        errx(400, "The number of arguments is invalid.");
    }

    for (int i = 0; i < hidden_neuron; i++)
        free(w_input[i]);
    free(w_input);

    for (int i = 0; i < output_neuron; i++)
        free(w_output[i]);
    free(w_output);

    free(b_input);
    free(b_output);

    return 0;
}
