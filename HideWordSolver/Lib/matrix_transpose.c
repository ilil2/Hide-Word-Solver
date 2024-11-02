#include "lib.h"

// Transpose a matrix
void matrix_transpose(size_t x, size_t y, double **mat1,
		double **res)
{
	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			res[j][i] = mat1[i][j];
		}
	}
}
