#include "neural_network.h"

char predict(double *input,
        double *hidden,
		double *output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output)
{
    forward(input, hidden, output, w_input, w_output, b_input, b_output);

    return convert_output_to_char(output);
}
