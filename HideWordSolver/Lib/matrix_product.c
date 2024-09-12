#include <err.h>
#include "lib.h"

void matrix_product(size_t row1, size_t col1, int mat1[row1][col1],
		size_t row2, size_t col2, int mat2[row2][col2], int res[row1][col2])
{
	if(col1 == row2)
	{
    	for(size_t i = 0; i < row1; i++)
		{
			for(size_t j = 0; j < col2; j++)
			{
				int add = 0;
				for(size_t k = 0; k < col1; k++)
				{
					add += mat1[i][k] * mat2[k][j];
				}
				res[i][j] = add;
			}
		}
	}
	else
	{
		errx(3, "Impossible to multiply the two matrices.");
	}
}
