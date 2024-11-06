#include "lib.h"

// adition of matrix
void matrix_addition(size_t row, size_t col, float **mat1,
		float **mat2, float **res)
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
		{
			res[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
}
