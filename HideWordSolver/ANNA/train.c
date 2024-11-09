#include "neural_network.h"

void train(int nb_letter,
		char *anna_result,	// nb_letter
		float** w_input,   // hidden_neuron1 x input_neuron
        float** w_hidden,  // hidden_neuron2 x hidden_neuron1
		float** w_output,  // output_neuron x hidden_neuron2
		float* b_input,    // hidden_neuron1
		float* b_hidden,   // hidden_neuron2
		float* b_output,   // output_neuron
		int threads)
{
	if(nb_letter > 13001)
	{
		nb_letter = 13001;
	}

	size_t test_size = 20748;

	// Memory allocations //

	// Train allocations
	float** input = malloc(sizeof(float*) * input_neuron);
	for (int i = 0; i < input_neuron; i++)
	{
		input[i] = malloc(sizeof(float) * nb_letter);
	}

	float** hidden1 = malloc(sizeof(float*) * hidden_neuron1);
	for (int i = 0; i < hidden_neuron1; i++)
	{
		hidden1[i] = malloc(sizeof(float) * nb_letter);
	}

	float** hidden2 = malloc(sizeof(float*) * hidden_neuron2);
	for (int i = 0; i < hidden_neuron2; i++)
	{
		hidden2[i] = malloc(sizeof(float) * nb_letter);
	}

	float** output = malloc(sizeof(float*) * output_neuron);
	float** expected_output = malloc(sizeof(float*) * output_neuron);
	float** output_error = malloc(sizeof(float*) * output_neuron);
	float** dw_output = malloc(sizeof(float*) * output_neuron);
	float** m_w_output = malloc(sizeof(float*) * output_neuron);
	float** v_w_output = malloc(sizeof(float*) * output_neuron);
	float* db_output = malloc(sizeof(float) * output_neuron);
	float* m_b_output = malloc(sizeof(float) * output_neuron);
	float* v_b_output = malloc(sizeof(float) * output_neuron);
	for (int i = 0; i < output_neuron; i++)
	{
		output[i] = malloc(sizeof(float) * nb_letter);
		expected_output[i] = malloc(sizeof(float) * nb_letter);
		output_error[i] = malloc(sizeof(float) * nb_letter);
		dw_output[i] = malloc(sizeof(float) * hidden_neuron2);
		m_w_output[i] = malloc(sizeof(float) * hidden_neuron2);
		v_w_output[i] = malloc(sizeof(float) * hidden_neuron2);
	}

	float** hidden2_error = malloc(sizeof(float*) * hidden_neuron2);
	float** dw_hidden = malloc(sizeof(float*) * hidden_neuron2);
	float** m_w_hidden = malloc(sizeof(float*) * hidden_neuron2);
	float** v_w_hidden = malloc(sizeof(float*) * hidden_neuron2);
	float* db_hidden = malloc(sizeof(float) * hidden_neuron2);
	float* m_b_hidden = malloc(sizeof(float) * hidden_neuron2);
	float* v_b_hidden = malloc(sizeof(float) * hidden_neuron2);
	for (int i = 0; i < hidden_neuron2; i++)
	{
		hidden2_error[i] = malloc(sizeof(float) * nb_letter);
		dw_hidden[i] = malloc(sizeof(float) * hidden_neuron1);
		m_w_hidden[i] = malloc(sizeof(float) * hidden_neuron1);
		v_w_hidden[i] = malloc(sizeof(float) * hidden_neuron1);
	}

	float** hidden1_error = malloc(sizeof(float*) * hidden_neuron1);
	float** dw_input = malloc(sizeof(float*) * hidden_neuron1);
	float** m_w_input = malloc(sizeof(float*) * hidden_neuron1);
	float** v_w_input = malloc(sizeof(float*) * hidden_neuron1);
	float* db_input = malloc(sizeof(float) * hidden_neuron1);
	float* m_b_input = malloc(sizeof(float) * hidden_neuron1);
	float* v_b_input = malloc(sizeof(float) * hidden_neuron1);
	for (int i = 0; i < hidden_neuron1; i++)
	{
		hidden1_error[i] = malloc(sizeof(float) * nb_letter);
		dw_input[i] = malloc(sizeof(float) * input_neuron);
		m_w_input[i] = malloc(sizeof(float) * input_neuron);
		v_w_input[i] = malloc(sizeof(float) * input_neuron);
	}

	// Test allocations
	float** test_input = malloc(sizeof(float*) * input_neuron);
	for (size_t i = 0; i < input_neuron; i++)
	{
		test_input[i] = malloc(sizeof(float) * test_size);
	}

	float** test_hidden1 = malloc(sizeof(float*) * hidden_neuron1);
	for (size_t i = 0; i < hidden_neuron1; i++)
	{
		test_hidden1[i] = malloc(sizeof(float) * test_size);
	}

	float** test_hidden2 = malloc(sizeof(float*) * hidden_neuron2);
	for (size_t i = 0; i < hidden_neuron2; i++)
	{
		test_hidden2[i] = malloc(sizeof(float) * test_size);
	}

	float** test_output = malloc(sizeof(float) * output_neuron);
	float** test_expected = malloc(sizeof(float*) * output_neuron);
	for (size_t i = 0; i < output_neuron; i++)
	{
		test_output[i] = malloc(sizeof(float) * test_size);
		test_expected[i] = malloc(sizeof(float) * test_size);
	}

	char* anna_expected_result = malloc(nb_letter * sizeof(char));

	//////////////////////

	char dataset_order[nb_dataset];

	for (int i = 0; i < nb_dataset; i++)
	{
		dataset_order[i] = i;
	}

	HyperParam hp;
	Param p;
	Adam a;
	Test t;
	Info i;
	Var v;

	load_hyperparameter(&hp, &a, &v);

	ANNA anna = {
		&hp,
		&p,
		&a,
		&t,
		&i,
		&v
	};

	// Loading neural network biases and weights
	load_parameter(w_input, w_hidden, w_output, b_input, b_hidden, b_output);
	size_t nb_while = 42;

	while (nb_while)
	{
		//nb_while -= 1;
		anna.v->epoch++;

		printf("Epoch : %zu\n", anna.v->epoch);

		// Mixing the dataset
		shuffle(dataset_order, nb_dataset);

		float train_success_t = 0;
		float log_loss_t = 0;

		// Update dropout rate
		anna.hp->dropout_rate = anna.hp->init_dropout_rate
			* exp(-anna.hp->dropout_decay_rate * anna.v->epoch);
		if (anna.hp->dropout_rate < anna.hp->min_dropout_rate)
		{
			anna.hp->dropout_rate = anna.hp->min_dropout_rate;
		}

		for (int i = 0; i < nb_dataset; i++)
		{
			anna.a->t++;
			printf("\t%i, Data Set %i :\n", i, dataset_order[i]);
			// Loading images
			load_image("Dataset/Train/", dataset_order[i], nb_letter, input,
				expected_output);

			// Mixing dataset images
			matrix_shuffle(input, expected_output, input_neuron,
				output_neuron, nb_letter);

			// Applying forward propagation
			forward(nb_letter, input, hidden1, hidden2, output, w_input,
				w_hidden, w_output, b_input, b_hidden, b_output,
				anna.hp->dropout_rate, threads);

			// Applying back propagation
			backward(nb_letter, w_output, w_hidden, input, hidden1, hidden2,
				output, expected_output, output_error, dw_output,
				db_output, hidden2_error, dw_hidden, db_hidden, hidden1_error,
				dw_input, db_input, threads);

			// Applying Adam optimizer
			update(w_input, w_hidden, w_output, b_input, b_hidden, b_output,
            	dw_output, db_output, dw_hidden, db_hidden, dw_input, db_input,
            	m_w_input, v_w_input, m_w_hidden, v_w_hidden, m_w_output,
				v_w_output, m_b_input, v_b_input, m_b_hidden, v_b_hidden,
            	m_b_output, v_b_output, anna.hp->learning_rate, anna.a->beta1,
				anna.a->beta2, anna.hp->espilon, anna.hp->lambda, anna.a->t);

			// Applying softmax function
			softmax(nb_letter, output);

			// Check result
			convert_output_to_char(nb_letter, output, anna_result);
			convert_output_to_char(nb_letter, expected_output,
				anna_expected_result);
			float success = 0;
			for (int i = 0; i < nb_letter; i++)
			{
				if (anna_result[i] == anna_expected_result[i])
				{
					success += 1;
				}
			}
			float _log_loss = log_loss(nb_letter, expected_output, output);
			train_success_t += success / nb_letter;
			log_loss_t += _log_loss;

			printf("\t\tLog Loss (%i) = %f\n", i, _log_loss);
			printf("\t\tSuccess (%i) = %f\n", i, success / nb_letter);
		}
		printf("\n");

		// Update learning rate
		if (log_loss_t > anna.hp->best_loss - anna.hp->espilon)
		{
			anna.hp->change_iteration += 1;

			if (anna.hp->change_iteration >= anna.hp->max_change_iteration)
			{
				anna.hp->learning_rate *= anna.hp->learning_decay_rate;
				anna.hp->change_iteration = 0;
			}
		}
		else
		{
			anna.hp->best_loss = log_loss_t;
			anna.hp->change_iteration = 0;
		}
		
		// Save parameter and stats
		if (anna.v->epoch % 1 == 0)
		{
			printf("\tTotal log loss = %f\n", log_loss_t / nb_dataset);
			printf("\tTotal train success = %f\n", train_success_t / nb_dataset);
			float test_succes_t = test(test_size, test_input, test_hidden1,
				test_hidden2, test_expected, test_output, w_input, w_hidden,
				w_output, b_input, b_hidden, b_output, threads);
			save_stats(anna.v->epoch, log_loss_t / nb_dataset, train_success_t / nb_dataset,
				test_succes_t);
			save_parameter(w_input, w_hidden, w_output, b_input, b_hidden, b_output);
			save_hyperparameter(&anna);
			printf("\tSave ! \n\n");
		}
	}

	// Memory release //

	// Train allocations
	for (int i = 0; i < input_neuron; i++) {
		free(input[i]);
	}
	free(input);

	for (int i = 0; i < hidden_neuron1; i++) {
		free(hidden1[i]);
	}
	free(hidden1);

	for (int i = 0; i < hidden_neuron2; i++) {
		free(hidden2[i]);
	}
	free(hidden2);

	for (int i = 0; i < output_neuron; i++) {
		free(output[i]);
		free(expected_output[i]);
		free(output_error[i]);
		free(dw_output[i]);
		free(m_w_output[i]);
		free(v_w_output[i]);
	}
	free(output);
	free(expected_output);
	free(output_error);
	free(dw_output);
	free(m_w_output);
	free(v_w_output);
	free(db_output);
	free(m_b_output);
	free(v_b_output);

	for (int i = 0; i < hidden_neuron2; i++) {
		free(hidden2_error[i]);
		free(dw_hidden[i]);
		free(m_w_hidden[i]);
		free(v_w_hidden[i]);
	}
	free(hidden2_error);
	free(dw_hidden);
	free(m_w_hidden);
	free(v_w_hidden);
	free(db_hidden);
	free(m_b_hidden);
	free(v_b_hidden);

	for (int i = 0; i < hidden_neuron1; i++) {
		free(hidden1_error[i]);
		free(dw_input[i]);
		free(m_w_input[i]);
		free(v_w_input[i]);
	}
	free(hidden1_error);
	free(dw_input);
	free(m_w_input);
	free(v_w_input);
	free(db_input);
	free(m_b_input);
	free(v_b_input);

	// Test allocations
	for (size_t i = 0; i < input_neuron; i++) {
		free(test_input[i]);
	}
	free(test_input);

	for (size_t i = 0; i < hidden_neuron1; i++) {
		free(test_hidden1[i]);
	}
	free(test_hidden1);

	for (size_t i = 0; i < hidden_neuron2; i++) {
		free(test_hidden2[i]);
	}
	free(test_hidden2);

	for (size_t i = 0; i < output_neuron; i++) {
		free(test_output[i]);
		free(test_expected[i]);
	}
	free(test_output);
	free(test_expected);

	free(anna_expected_result);

	//////////////////////
}
