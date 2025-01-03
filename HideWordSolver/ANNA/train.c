#include "neural_network.h"

void train(ANNA* anna)
{
	char dataset_order[anna->v->batch_nb];

	for (size_t i = 0; i < anna->v->batch_nb; i++)
	{
		dataset_order[i] = i;
	}

	// Loading neural network biases and weights
	size_t nb_while = 42;

	while (nb_while)
	{
		//nb_while -= 1;
		anna->v->epoch++;

		printf("Epoch : %zu\n", anna->v->epoch);

		// Mixing the dataset
		shuffle(dataset_order, anna->v->batch_nb);

		float train_success_t = 0;
		float log_loss_t = 0;

		// Update dropout rate
		anna->hp->dropout_rate = anna->hp->init_dropout_rate
			- anna->hp->dropout_decay_rate * anna->v->epoch;

		if (anna->hp->dropout_rate < anna->hp->min_dropout_rate)
		{
			anna->hp->dropout_rate = anna->hp->min_dropout_rate;
		}

		for (size_t i = 0; i < anna->v->batch_nb; i++)
		{
			printf("\t%zu, Data Set %i :\n", i, dataset_order[i]);
			// Loading images
			load_dataset("Dataset/Train/", dataset_order[i], anna);

			// Mixing dataset images
			matrix_shuffle(anna->p->neuron[0], anna->p->expected_output,
				anna->i->nb_neuron[0], anna->i->nb_neuron[anna->i->nb_layer-1],
				anna->v->train_data);

			// Applying forward propagation
			forward(anna);

			// Check result
			convert_output_to_char(anna->v->train_data,
				anna->i->nb_neuron[anna->i->nb_layer-1],
				anna->p->neuron[anna->i->nb_layer-1],
				anna->p->result[0]);
			convert_output_to_char(anna->v->train_data,
				anna->i->nb_neuron[anna->i->nb_layer-1],
				anna->p->expected_output,
				anna->p->result[1]);
			float success = 0;
			for (size_t i = 0; i < anna->v->train_data; i++)
			{
				if (anna->p->result[0][i] == anna->p->result[1][i])
				{
					success += 1;
				}
			}
			float _log_loss = log_loss(anna);
			train_success_t += success / anna->v->train_data;
			log_loss_t += _log_loss;

			// Applying back propagation
			backward(anna);

			// Applying Adam optimizer
			update(anna);

			printf("\t\tLog Loss (%zu) = %f\n", i, _log_loss);
			printf("\t\tSuccess (%zu) = %f\n", i,
				success / anna->v->train_data);
		}
		printf("\n");
		
		// Save parameter and stats
		if (anna->v->epoch % 1 == 0)
		{
			printf("\tTotal log loss = %f\n", log_loss_t / anna->v->batch_nb);
			printf("\tTotal train success = %f\n",
					train_success_t / anna->v->batch_nb);
			float test_succes_t = test(anna);
			save_stats(anna->v->epoch, log_loss_t / anna->v->batch_nb,
				train_success_t / anna->v->batch_nb, test_succes_t);
			save_parameter(anna->p, anna->i);
			save_hyperparameter(anna);
			printf("\tSave ! \n\n");
		}
	}
}
