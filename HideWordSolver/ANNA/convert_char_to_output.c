#include "neural_network.h"

void convert_char_to_output(char c, double *output)
{
	output = {};
	output[c - 'A'] = 1;
}
