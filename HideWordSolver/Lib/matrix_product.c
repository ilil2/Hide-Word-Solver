#include <err.h>
#include "lib.h"
#include <pthread.h>
#include <stdlib.h>

// Mutultipy two matrix (multithreading)
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
} MatrixProductThreadData;

void *_matrix_product(void *arg);

void matrix_product(size_t row1, size_t col1, double **mat1,
		size_t row2, size_t col2, double **mat2, double **res,
		size_t thread_nbr)
{
	if(col1 == row2)
	{
		pthread_t threads[thread_nbr];
		MatrixProductThreadData *thread_data[thread_nbr];

		for (size_t i = 0; i < thread_nbr; i++)
		{
			size_t start_row = (i * row1) / thread_nbr;
			size_t end_row = ((i + 1) * row1) / thread_nbr;

			thread_data[i] = malloc(sizeof(MatrixProductThreadData));
			*thread_data[i] = (MatrixProductThreadData){mat1, mat2, res,
				start_row, end_row, row1, col2, col1};
			pthread_create(&threads[i], NULL, _matrix_product, thread_data[i]);
		}

		for (size_t i = 0; i < thread_nbr; i++)
		{
			pthread_join(threads[i], NULL);
			free(thread_data[i]);
		}
	}
	else
	{
		errx(3, "Impossible to multiply the two matrices.");
	}
}

void *_matrix_product(void *arg)
{
	MatrixProductThreadData* data = (MatrixProductThreadData*)arg;
	for (size_t i = data->start_row; i < data->end_row; i++)
	{
		for (size_t j = 0; j < data->col; j++)
		{
			data->mat3[i][j] = 0;
			for (size_t k = 0; k < data->both; k++)
			{
				data->mat3[i][j] += data->mat1[i][k] * data->mat2[k][j];
			}
		}
	}

	return NULL;
}
