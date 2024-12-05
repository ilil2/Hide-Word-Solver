#include "neural_network.h"

void predict(ANNA* anna, char* directory, size_t grid_width,
	size_t grid_height, size_t word_nb)
{
	char grid_buffer[100];
    snprintf(grid_buffer, sizeof(grid_buffer), "%s/grid.csv", directory);

	anna->v->train_data = grid_width * grid_height;
	anna->p = init_param(anna->i, anna->v, 1);

    load_parameter(anna->p, anna->i);
	load_image(grid_buffer, anna);

    forward(anna);
	
    convert_output_to_char(anna->v->train_data,
		anna->i->nb_neuron[anna->i->nb_layer-1],
		anna->p->neuron[anna->i->nb_layer-1],
		anna->p->result[0]);

	snprintf(grid_buffer, sizeof(grid_buffer), "%s/grid.txt", directory);

	save_grid(grid_buffer, grid_width, grid_height, anna->p->result[0]);

	free_param(anna->p, anna->i, anna->v, 1);

	for (size_t i = 0; i < word_nb; i++)
	{
		char word_buffer[100];
    	snprintf(word_buffer, sizeof(word_buffer), "%s/word_%zu.csv", directory, i);

		FILE* file = fopen(word_buffer, "r");
		size_t word_size = 0;
		int c;
		while((c = fgetc(file)) != EOF)
		{
			if(c == '\n')
			{
				word_size += 1;
			}
		}
		fclose(file);

		anna->v->train_data = word_size;
		anna->p = init_param(anna->i, anna->v, 1);

    	load_parameter(anna->p, anna->i);
		load_image(word_buffer, anna);

		forward(anna);

		convert_output_to_char(anna->v->train_data,
		anna->i->nb_neuron[anna->i->nb_layer-1],
		anna->p->neuron[anna->i->nb_layer-1],
		anna->p->result[0]);

		snprintf(word_buffer, sizeof(word_buffer), "%s/word_%zu.txt", directory, i);

		save_word(word_buffer, word_size, anna->p->result[0]);

		free_param(anna->p, anna->i, anna->v, 1);
	}
	
}
