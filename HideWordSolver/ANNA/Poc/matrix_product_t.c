#include "poc.h"

void matrix_product_t(size_t row1, size_t col1, double **mat1,
        size_t row2, size_t col2, double **mat2, double **res,
		char trans_nbr)
{
    if (((col1 == col2) && trans_nbr) ||
        ((row1 == row2) && !trans_nbr))
    {
        if (trans_nbr)
        {
            for (size_t i = 0; i < row1; i++)
            {
                for (size_t j = 0; j < col2; j++)
                {
                    res[i][j] = 0;
                    for (size_t k = 0; k < col1; k++)
                    {
                        res[i][j] += mat1[i][k] * mat2[j][k];
                    }
                }
            }
        }
        else
        {
            for (size_t i = 0; i < row1; i++)
            {
                for (size_t j = 0; j < col2; j++)
                {
                    res[i][j] = 0;
                    for (size_t k = 0; k < row2; k++)
                    {
                        res[i][j] += mat1[k][i] * mat2[k][j];
                    }
                }
            }
        }
    }
    else
    {
        errx(3, "Impossible to multiply the two matrices.");
    }
}