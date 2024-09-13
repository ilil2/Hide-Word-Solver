#include "lib.h"

void matrix_addition(size_t row, size_t col, const double mat1[row][col],
		const double mat2[row][col], double res[row][col])
{
	for (size_t i = 0; i < row; i++)
	{
		for (size_t i = 0; i < col; i++)
		{
			res[i][j] = mat1[i][j] + mat2[i][j];
		}
	}
}
