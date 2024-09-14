#include "neural_network.h"
#include <err.h>

int main(int argc, char** argv)
{
    if(argc > 1)
    {
        if (strcomp(argv[1], "reset"))
        {
            printf("Resetting ANNA parameters...");
            reset_parameter(w_input, w_output, b_input, b_output);
            printf("ANNA's parameters have been reset.");
        }
        else if (strcomp(argv[1], "start"))
        {   
            printf("ANNA's character recognition activated !");
        }
        else
        {
            if (argc > 2)
            {
                printf("ANNA's training start.");

                size_t data_size = atoi(argv[2]);
                double input[data_size][input_neuron];

                load_image("Dataset/Train/A.csv", data_size, input);
            }
            else
            {
                errx(10, "The number of images to be taken has not been indicated.");
            }
        }
    }
    else
    {
        errx(400, "The number of arguments is invalid.");
    }

    return 0;
}
