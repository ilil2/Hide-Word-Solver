#include "neural_network.h"

void convert_char_to_output(char c, size_t row, size_t col, double **output)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			output[i][j] = 0;
			output[i][c - 'A'] = 1;
		}
	}
}
