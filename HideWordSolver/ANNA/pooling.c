#include "neural_network.h"

//#define image_size 4

void pooling(size_t nb_letter,
		double **input, //(image_size - 2)² x nb_letter
		size_t output_size,
		double **output) //output_size x nb_letter
{
	size_t mod_row = image_size / output_size;
	for (size_t i = 0; i < nb_letter; i++)
	{
		for (size_t block = 0; block < output_size * output_size; block++)
		{
			double avg = 0;
			for (size_t j = mod_row * (block % output_size);
					j < mod_row * (block % output_size) + mod_row; j++)
			{
				for (size_t k = (block / output_size) * mod_row;
						k < (block / output_size) * mod_row + mod_row; k++)
				{
					//printf("%f\n", input[k * image_size + j][i]);
					avg += input[k * image_size + j][i];
					//printf("max : %f\n", max);
				}
			}
			output[block][i] = avg / (mod_row * mod_row);
			//printf("new\n\n\n");
		}
	}
}

/*int main(int argc, char **argv)
{
	double i[16][1]  = {{125.0},	{3.0}, 		{1.0}, 		{2.0},
						{124.0}, 	{122.0}, 	{255.0}, 	{0.0},
						{0.0}, 		{0.0}, 		{1.0}, 		{0.0},
						{0.0}, 		{0.0}, 		{0.0}, 		{0.0}};

	double o[4][1] = {	{0.0}, {0.0},
						{0.0}, {0.0}};
	pooling(1, i, 2, o);

	for (size_t i = 0; i < 4; i++)
	{
		printf("%f, ", o[i][0]);
	}
}*/
