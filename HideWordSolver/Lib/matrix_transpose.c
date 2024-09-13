#include "lib.h"

void matrix_transpose(size_t x, size_t y, const double mat1[x][y],
		double res[y][x])
{
	for (size_t i = 0; i < x; i++)
	{
		for (size_t j = 0; j < y; j++)
		{
			res[j][i] = mat1[i][j];
		}
	}
}
