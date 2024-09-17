#include <err.h>
#include "lib.h"
#include <threads.h>

typedef struct
{
	double **mat1;
	double **mat2;
	double **mat3;
	size_t start_row;
	size_t end_row;
	size_t row;
	size_t col;
	size_t both;
	char trans_nbr;
} MatrixProductThreadData

void matrix_product_t(size_t row1, size_t col1, double **mat1,
        size_t row2, size_t col2, double **mat2, double **res,
		char trans_nbr = 0, size_t thread_nbr = 1)
{
    if(col1 == col2)
    {
		thrd_t threads[thread_nbr];

		for (size_t i = 0; i < thread_nbr; i++)
		{
			size_t start_row = (i * row1) / thread_nbr;
			size_t end_row = ((i + 1) * row1) / thread_nbr;


			MatrixProductThreadData* data;
			if (trans_nbr)
			{
				data = {mat1, mat2, res, start_row,
					end_row, row1, row2, col1};
			}
			else
			{
				data = {mat1, mat2, res, start_row,
					end_row, col1, col2, row1};
			}
			
			thrd_create(&threads[i], _matrix_product_t, data);
		}

		for (size_t i = 0; i < thread_nbr; i++)
		{
			thrd_join(threads[i]);
		}
        for(size_t i = 0; i < row1; i++)
        {
            for(size_t j = 0; j < row2; j++)
            {
                double add = 0;
                for(size_t k = 0; k < col1; k++)
                {
                    add += mat1[i][k] * mat2[j][k];
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

void _matrix_product_t(void *arg)
{
	MatrixProductThreadData* data = (MatrixProductThreadData*)arg;

	if (trans_nbr)
	{
		for (size_t i = data->start_row; i < data->end_row; i++)
		{
			for (size_t j = 0; i < data->col; j++)
			{
				mat3[i][j] = 0;
				for (size_t k = 0; k < data->both; k++)
				{
					mat3[i][j] += mat1[i][k] * mat2[j][k];
				}
			}
		}
	}
	else
	{
		for (size_t i = data->start_row; i < data->end_row; i++)
		{
			for (size_t j = 0; j < data->col; j++)
			{
				mat3[i][j] = 0;
				for (size_t k = 0; k < data->both; k++)
				{
					mar3[i][j] += mat1[j][i] * mat2[k][j];
				}
			}
		}
	}
}
