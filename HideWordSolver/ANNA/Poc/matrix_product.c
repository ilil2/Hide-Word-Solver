#include "poc.h"

void matrix_product(size_t row1, size_t col1, double **mat1,
		size_t row2, size_t col2, double **mat2, double **res)
{
	if(col1 == row2)
	{
        for (size_t i = 0; i < row1; i++)
        {
            for (size_t j = 0; j < col2; j++)
            {
                double add = 0;
                for (size_t k = 0; k < col1; k++)
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