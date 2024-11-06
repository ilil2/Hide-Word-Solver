#include "neural_network.h"

void pooling(size_t nb_letter,
		float **input, //(image_size - 2)² x nb_letter
		size_t output_size,
		float **output) //output_size x nb_letter
{
	size_t mod_row = image_size / output_size;
	for (size_t i = 0; i < nb_letter; i++)
	{
		for (size_t block = 0; block < output_size * output_size; block++)
		{
			float avg = 0;
			for (size_t j = mod_row * (block % output_size);
					j < mod_row * (block % output_size) + mod_row; j++)
			{
				for (size_t k = (block / output_size) * mod_row;
						k < (block / output_size) * mod_row + mod_row; k++)
				{
					avg += input[k * image_size + j][i];
				}
			}
			output[block][i] = avg / (mod_row * mod_row);
		}
	}
}
