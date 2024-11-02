#include "neural_network.h"

void predict(int nb_letter,
		char *anna_result,
		double **input,
        double **hidden,
		double **output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output,
		double threads)
{
    forward(nb_letter, input, hidden, output, w_input, w_output,
		b_input, b_output, -1, threads);

    convert_output_to_char(nb_letter, output, anna_result);
}
