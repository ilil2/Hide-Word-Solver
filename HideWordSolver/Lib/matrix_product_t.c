#include <err.h>
#include "lib.h"
#include <pthread.h>

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
} MatrixProductThreadData;

void *_matrix_product_t(void *arg);

void matrix_product_t(size_t row1, size_t col1, double **mat1,
        size_t row2, size_t col2, double **mat2, double **res,
		char trans_nbr, size_t thread_nbr)
{
    if(col1 == col2)
    {
		pthread_t threads[thread_nbr];

		for (size_t i = 0; i < thread_nbr; i++)
		{
			size_t start_row = (i * row1) / thread_nbr;
			size_t end_row = ((i + 1) * row1) / thread_nbr;


			MatrixProductThreadData data = {mat1, mat2, res, start_row,
					end_row, row1, row2, col1};
			if (!trans_nbr)
			{
				data.row = col1;
				data.col = col2;
				data.both = row1;
			}			
			pthread_create(&threads[i], NULL, _matrix_product_t, &data);
		}

		for (size_t i = 0; i < thread_nbr; i++)
		{
			pthread_join(threads[i], NULL);
		}
    }
    else
    {
        errx(3, "Impossible to multiply the two matrices.");
    }
}

void *_matrix_product_t(void *arg)
{
	MatrixProductThreadData* data = (MatrixProductThreadData*)arg;

	if (data->trans_nbr)
	{
		for (size_t i = data->start_row; i < data->end_row; i++)
		{
			for (size_t j = 0; i < data->col; j++)
			{
				data->mat3[i][j] = 0;
				for (size_t k = 0; k < data->both; k++)
				{
					data->mat3[i][j] += data->mat1[i][k] * data->mat2[j][k];
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
				data->mat3[i][j] = 0;
				for (size_t k = 0; k < data->both; k++)
				{
					data->mat3[i][j] += data->mat1[j][i] * data->mat2[k][j];
				}
			}
		}
	}
}
