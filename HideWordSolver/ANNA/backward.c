#include "neural_network.h"

void backward(int nb_letter,
              double **w_output,        // output_neuron x hidden_neuron2
              double **w_hidden,        // hidden_neuron2 x hidden_neuron1
              double **input,           // input_neuron x nb_letter
              double **hidden1,         // hidden_neuron1 x nb_letter
              double **hidden2,         // hidden_neuron2 x nb_letter
              double **output,          // output_neuron x nb_letter
              double **expected_output, // output_neuron x nb_letter
              double **output_error,    // output_neuron x nb_letter
              double **dw_output,       // output_neuron x hidden_neuron2
              double *db_output,        // output_neuron
              double **hidden2_error,   // hidden_neuron2 x nb_letter
              double **dw_hidden,       // hidden_neuron2 x hidden_neuron1
              double *db_hidden,        // hidden_neuron2
              double **hidden1_error,   // hidden_neuron1 x nb_letter
              double **dw_input,        // hidden_neuron1 x input_neuron
              double *db_input,         // hidden_neuron1
              char threads)
{
    // Apply back propagation on weights and biases between output and second hidden layer
    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            output_error[i][j] = (output[i][j] - expected_output[i][j])
                * activ_prime(output[i][j]);
        }
    }

    matrix_product_t(output_neuron, nb_letter, output_error, hidden_neuron2,
        nb_letter, hidden2, dw_output, 1, threads);

    for (int i = 0; i < output_neuron; i++)
    {
        for (int j = 0; j < hidden_neuron2; j++)
        {
            dw_output[i][j] /= nb_letter;
        }
    }

    for (int i = 0; i < output_neuron; i++)
    {
        double sum = 0;
        for (int j = 0; j < nb_letter; j++)
        {
            sum += output_error[i][j];
        }
        db_output[i] = sum / nb_letter;
    }

    matrix_product_t(output_neuron, hidden_neuron2, w_output, output_neuron,
        nb_letter, output_error, hidden2_error, 0, threads);

    // Apply back propagation on weights and biases between second hidden layer and first hidden layer
    for (int i = 0; i < hidden_neuron2; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            hidden2_error[i][j] *= activ_prime(hidden2[i][j]);
        }
    }

    matrix_product_t(hidden_neuron2, nb_letter, hidden2_error, hidden_neuron1,
        nb_letter, hidden1, dw_hidden, 1, threads);

    for (int i = 0; i < hidden_neuron2; i++)
    {
        for (int j = 0; j < hidden_neuron1; j++)
        {
            dw_hidden[i][j] /= nb_letter;
        }
    }

    for (int i = 0; i < hidden_neuron2; i++)
    {
        double sum = 0;
        for (int j = 0; j < nb_letter; j++)
        {
            sum += hidden2_error[i][j];
        }
        db_hidden[i] = sum / nb_letter;
    }

    matrix_product_t(hidden_neuron2, hidden_neuron1, w_hidden, hidden_neuron2,
        nb_letter, hidden2_error, hidden1_error, 0, threads);

    // Apply back propagation on weights and biases between first hidden layer and input
    for (int i = 0; i < hidden_neuron1; i++)
    {
        for (int j = 0; j < nb_letter; j++)
        {
            hidden1_error[i][j] *= activ_prime(hidden1[i][j]);
        }
    }

    matrix_product_t(hidden_neuron1, nb_letter, hidden1_error, input_neuron,
        nb_letter, input, dw_input, 1, threads);

    for (int i = 0; i < hidden_neuron1; i++)
    {
        for (int j = 0; j < input_neuron; j++)
        {
            dw_input[i][j] /= nb_letter;
        }
    }

    for (int i = 0; i < hidden_neuron1; i++)
    {
        double sum = 0;
        for (int j = 0; j < nb_letter; j++)
        {
            sum += hidden1_error[i][j];
        }
        db_input[i] = sum / nb_letter;
    }
}