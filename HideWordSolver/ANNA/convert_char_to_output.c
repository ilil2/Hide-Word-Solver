#include "neural_network.h"

void convert_char_to_output(char c, size_t size, double *output)
{
	for (size_t i = 0; i < size; i++)
	{
		output[i] = 0;
	}
	
	output[c - 'A'] = 1;
}
