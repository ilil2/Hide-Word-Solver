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
	size_t r;
	for (r = 0; r < anna->i->nb_layer - 1; r++)
	{
		for (size_t j = 0; j < anna->i->nb_neuron[r+1]; j++)
		{
			anna->p->neuron_error[r][j] = (float*)realloc(anna->p->neuron_error[r][j], anna->v->test_data *
						sizeof(float));
			if (anna->p->neuron_error[r][j] == NULL)
			{
				err(1, "realloc()");
			}
		}

		for (size_t j = 0; j < anna->i->nb_neuron[r]; j++)
		{
			anna->p->neuron[r][j] = realloc(anna->p->neuron[r][j], anna->v->test_data * sizeof(float));
			if (anna->p->neuron[r][j] == NULL)
			{
				err(1, "realloc()");
			}
		}
	}

	for (size_t j = 0; j < anna->i->nb_neuron[r]; j++)
	{
		anna->p->neuron[r][j] = realloc(anna->p->neuron[r][j], anna->v->test_data * sizeof(float));
		anna->p->expected_output[j] = realloc(anna->p->expected_output[j], sizeof(float) * anna->v->test_data);

		if (anna->p->neuron[r][j] == NULL || anna->p->expected_output[j] == NULL)
		{
			err(1, "realloc()");
		}
	}
	
	for (size_t j = 0; j < 2; j++)
	{
		anna->p->result[j] = realloc(anna->p->result[j], sizeof(float) * anna->v->test_data);

		if (anna->p->result[j] == NULL)
		{
			err(1, "realloc()");
		}
	}

	size_t save_train_data = anna->v->train_data;
	anna->v->train_data = anna->v->test_data;

	load_dataset("Dataset/Train/t", -1, anna);
	matrix_shuffle(anna->p->neuron[0], anna->p->expected_output,
		anna->i->nb_neuron[0], anna->i->nb_neuron[anna->i->nb_layer-1],
		anna->v->test_data);
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
			anna->p->neuron[anna->i->nb_layer-1], anna->p->expected_output};

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

	anna->v->train_data = save_train_data;

	for (r = 0; r < anna->i->nb_layer - 1; r++)
	{
		for (size_t j = 0; j < anna->i->nb_neuron[r+1]; j++)
		{
			anna->p->neuron_error[r][j] = (float*)realloc(anna->p->neuron_error[r][j], anna->v->train_data *
						sizeof(float));
			if (anna->p->neuron_error[r][j] == NULL)
			{
				err(1, "realloc()");
			}
		}

		for (size_t j = 0; j < anna->i->nb_neuron[r]; j++)
		{
			anna->p->neuron[r][j] = realloc(anna->p->neuron[r][j], anna->v->train_data * sizeof(float));
			if (anna->p->neuron[r][j] == NULL)
			{
				err(1, "realloc()");
			}
		}
	}

	for (size_t j = 0; j < anna->i->nb_neuron[r]; j++)
	{
		anna->p->neuron[r][j] = realloc(anna->p->neuron[r][j], anna->v->train_data * sizeof(float));
		anna->p->expected_output[j] = realloc(anna->p->expected_output[j], sizeof(float) * anna->v->train_data);

		if (anna->p->neuron[r][j] == NULL || anna->p->expected_output[j] == NULL)
		{
			err(1, "realloc()");
		}
	}
	
	for (size_t j = 0; j < 2; j++)
	{
		anna->p->result[j] = realloc(anna->p->result[j], sizeof(float) * anna->v->train_data);

		if (anna->p->result[j] == NULL)
		{
			err(1, "realloc()");
		}
	}

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
        for (size_t j = 0; j < data->output_neuron; j++)
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
