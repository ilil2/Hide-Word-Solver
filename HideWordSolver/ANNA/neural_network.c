#include "neural_network.h"

// Recognizes a letter of the alphabet using a neural network
// The first argument is the part of the program to be executed (reset, start or train)
// reset to reset model parameters
// start to begin character recognition
// train to train the AI with the number of images in the dataset as the second parameter and the number of threads to be used as the third parameter
int main(int argc, char** argv)
{
    float **w_input = malloc(hidden_neuron1 * sizeof(float *));
    for (int i = 0; i < hidden_neuron1; i++)
        w_input[i] = malloc(input_neuron * sizeof(float));

    float **w_hidden = malloc(hidden_neuron2 * sizeof(float *));
    for (int i = 0; i < hidden_neuron2; i++)
        w_hidden[i] = malloc(hidden_neuron1 * sizeof(float));

    float **w_output = malloc(output_neuron * sizeof(float *));
    for (int i = 0; i < output_neuron; i++)
        w_output[i] = malloc(hidden_neuron2 * sizeof(float));

    float *b_input = malloc(hidden_neuron1 * sizeof(float));

    float *b_hidden = malloc(hidden_neuron2 * sizeof(float));

    float *b_output = malloc(output_neuron * sizeof(float));

    if(argc > 1)
    {
        if (strcomp(argv[1], "reset"))
        {
            printf("Resetting ANNA parameters...\n");

            reset_parameter(w_input, w_hidden, w_output, b_input,
                b_hidden, b_output);

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
				char threads = 2;
				if (argc > 3)
				{
					threads = atoi(argv[3]);
				}
                int nb_letter = atoi(argv[2]);
                char *anna_result = malloc(nb_letter * sizeof(char));
                printf("ANNA's training start.\n");

                train(nb_letter, anna_result, w_input, w_hidden, w_output,
                    b_input, b_hidden, b_output, threads);
            }
            else
            {
                errx(10, "The number of images to be taken has not been "
                    "indicated.");
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

    for (int i = 0; i < hidden_neuron1; i++)
        free(w_input[i]);
    free(w_input);

    for (int i = 0; i < hidden_neuron2; i++)
        free(w_hidden[i]);
    free(w_hidden);

    for (int i = 0; i < output_neuron; i++)
        free(w_output[i]);
    free(w_output);

    free(b_input);
    free(b_hidden);
    free(b_output);

    return 0;
}
