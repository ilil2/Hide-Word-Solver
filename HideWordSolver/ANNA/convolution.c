#include "neural_network.h"

void convolution(int nb_letter,
                double **input,  // image_size^2 x nb_letter
                double **output, // image_size^2 x nb_letter
                double *filter1, // filter_size x filter_size
                double *filter2) // filter_size x filter_size
{
    for (int i = 0; i < nb_letter; i++)
    {
        for (size_t j = 0; j < image_size - filter_size + 1; j++)
        {
            for (size_t k = 0; k < image_size - filter_size + 1; k++)
            {
                double sum = 0;
                for (size_t l = 0; l < filter_size * filter_size; l++)
                {
                    sum += input[(j * image_size + k) + l % filter_size +
                                (image_size * (l / filter_size))][i] *
                                filter1[l];
                }
                output[j * image_size + k][i] = sum;
            }
        }
    }

    for (int i = 0; i < nb_letter; i++)
    {
        for (size_t j = 0; j < image_size - filter_size + 1; j++)
        {
            for (size_t k = 0; k < image_size - filter_size + 1; k++)
            {
                double sum = 0;
                for (size_t l = 0; l < filter_size * filter_size; l++)
                {
                    sum += input[(j * image_size + k) + l % filter_size +
                                (image_size * (l / filter_size))][i] *
                                filter2[l];
                }
                output[j * image_size + k][i] += sum;
            }
        }
    }

    for (int i = 0; i < nb_letter; i++)
    {
        for (size_t j = 0; j < image_size - filter_size + 1; j++)
        {
            for (size_t k = 0; k < image_size - filter_size + 1; k++)
            {
                double sum = 0;
                for (size_t l = 0; l < filter_size * filter_size; l++)
                {
                    sum += input[(j * image_size + k) + l % filter_size +
                                (image_size * (l / filter_size))][i] *
                                filter1[l];
                }
                output[j * image_size + k][i] += sum;
            }
        }
    }
}