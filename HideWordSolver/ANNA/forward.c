#include "neural_network.h"

void forward(int nb_letter,
             double **input,        // input_neuron x nb_letter
             double **hidden1,      // hidden_neuron1 x nb_letter
             double **hidden2,      // hidden_neuron2 x nb_letter
             double **output,       // output_neuron x nb_letter
             double **w_input,      // hidden_neuron1 x input_neuron
             double **w_hidden,     // hidden_neuron2 x hidden_neuron1
             double **w_output,     // output_neuron x hidden_neuron2
             double *b_input,       // hidden_neuron1
             double *b_hidden,      // hidden_neuron2
             double *b_output,      // output_neuron
             double dropout_rate,
             char threads)
{
    matrix_product(hidden_neuron1, input_neuron, w_input, input_neuron,
        nb_letter, input, hidden1, threads);

    for (int i = 0; i < hidden_neuron1; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            hidden1[i][j] += b_input[i];
            hidden1[i][j] = activ(hidden1[i][j]);

            if (dropout_rate > 0)
            {
                if ((double)rand() / RAND_MAX < dropout_rate)
                {
                    hidden1[i][j] = 0;
                }
                else
                {
                    hidden1[i][j] /= (1 - dropout_rate);
                }
            }
        }
    }

    matrix_product(hidden_neuron2, hidden_neuron1, w_hidden, hidden_neuron1,
        nb_letter, hidden1, hidden2, threads);

    for (int i = 0; i < hidden_neuron2; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            hidden2[i][j] += b_hidden[i];
            hidden2[i][j] = activ(hidden2[i][j]);

            if (dropout_rate > 0)
            {
                if ((double)rand() / RAND_MAX < dropout_rate)
                {
                    hidden2[i][j] = 0;
                }
                else
                {
                    hidden2[i][j] /= (1 - dropout_rate);
                }
            }
        }
    }

    matrix_product(output_neuron, hidden_neuron2, w_output, hidden_neuron2,
        nb_letter, hidden2, output, threads);

    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            output[i][j] += b_output[i];
            output[i][j] = activ(output[i][j]);
        }
    }
}
