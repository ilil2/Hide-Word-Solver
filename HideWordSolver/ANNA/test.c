#include "neural_network.h"

typedef struct
{
	size_t start;
	size_t end;
	size_t output_neuron;
	float **output;
	float **expected;
} ThreadTest;

void *_test(void *arg);

float test(ANNA* anna)
{
	load_dataset("Dataset/Train/t", -1, anna->v->test_data, test_input, test_expected);
	matrix_shuffle(test_input, test_expected, input_neuron, output_neuron, anna->v->test_data);
    forward(anna);

	float test_sum = 0;

	pthread_t threads[anna->v->threads];
	ThreadTest* data[anna->v->threads];

	for (size_t i = 0; i < (size_t)anna->v->threads; i++)
	{
		size_t start = (i * anna->v->test_data) / anna->v->threads;
    	size_t end = ((i + 1) * anna->v->test_data) / anna->v->threads;

		data[i] = malloc(sizeof(ThreadTest));
		*data[i] = (ThreadTest){start, end,
			anna->i->nb_neuron[anna->i->nb_layer-1],
			anna->p->neuron[anna->i->nb_layer-1], test_expected};

		pthread_create(&threads[i], NULL, _test, data[i]);
	}

	for (size_t i = 0; i < (size_t)anna->v->threads; i++)
	{
		int* res;
		pthread_join(threads[i], (void**)&res);
		free(data[i]);
		test_sum += *res;
		free(res);
	}
	
	test_sum /= (float)(anna->v->test_data);
	printf("\tTotal test success : %f\n", test_sum);

	return test_sum;
}

void *_test(void *arg)
{
	ThreadTest* data = (ThreadTest*)arg;
	int* sum = malloc(sizeof(int));
	*sum = 0;
	for (size_t i = data->start; i < data->end; i++)
    {
		float max = 0;
		size_t imax = 0;
		size_t imax_expected = 0;
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
