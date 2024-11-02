#include "neural_network.h"

typedef struct
{
	size_t start;
	size_t end;
	double **output;
	double **expected;
} ThreadTest;

void *_test(void *arg);

double test(size_t test_size,
		double **test_input,
		double **test_hidden1,
		double **test_hidden2,
		double **test_expected,
		double **test_output,
		double **w_input,
		double **w_hidden,
		double **w_output,
		double *b_input,
		double *b_hidden,
		double *b_output,
		char thread_nbr)
{
	load_image("Dataset/Train/t", -1, test_size, test_input, test_expected);
    forward(test_size, test_input, test_hidden1, test_hidden2, test_output,
		w_input, w_hidden, w_output, b_input, b_hidden, b_output, -1,
		thread_nbr);

	double test_sum = 0;

	pthread_t threads[thread_nbr];
	ThreadTest* data[thread_nbr];

	for (size_t i = 0; i < (size_t)thread_nbr; i++)
	{
		size_t start = (i * test_size) / thread_nbr;
    	size_t end = ((i + 1) * test_size) / thread_nbr;

		data[i] = malloc(sizeof(ThreadTest));
		*data[i] = (ThreadTest){start, end, test_output, test_expected};

		pthread_create(&threads[i], NULL, _test, data[i]);
	}

	for (size_t i = 0; i < (size_t)thread_nbr; i++)
	{
		int* res;
		pthread_join(threads[i], (void**)&res);
		free(data[i]);
		test_sum += *res;
		free(res);
	}
	
	test_sum /= (double)test_size;
	printf("\tTotal test success : %f\n", test_sum);
    fflush(stdout);

	return test_sum;
}

void *_test(void *arg)
{
	ThreadTest* data = (ThreadTest*)arg;
	int* sum = malloc(sizeof(int));
	*sum = 0;
	for (size_t i = data->start; i < data->end; i++)
    {
		double max = 0;
		size_t imax = 0;
		size_t imax_expected;
        for (size_t j = 0; j < output_neuron; j++)
        {
        	if (data->output[j][i] > max)
            {
            	max = data->output[j][i];
				imax = j;
            }
			if (data->expected[j][i] == 1)
			{
				imax_expected = j;
			}
		}
    	 *sum += imax == imax_expected;
    }
    pthread_exit((void*)sum);
}
