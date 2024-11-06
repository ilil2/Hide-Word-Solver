#include "neural_network.h"

void predict(int nb_letter,
		char *anna_result,
		float **input,
        float **hidden,
		float **output,
		float **w_input,
		float **w_output,
		float *b_input,
		float *b_output,
		float threads)
{
    forward(nb_letter, input, hidden, output, w_input, w_output,
		b_input, b_output, -1, threads);

    convert_output_to_char(nb_letter, output, anna_result);
}
