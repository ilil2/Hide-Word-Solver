#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>
#include <err.h>
#include "../Lib/lib.h"

#define input_neuron 1024
#define hidden_neuron 256
#define output_neuron 5

int main(int argc, char** argv);
void reset_parameter(double **w_input,
		double **w_output,
		double *b_input,
		double *b_output);
void save_parameter(const double **w_input,
		const double **w_output,
		const double *b_input,
		const double *b_output);
void load_parameter(double **w_input,
		double **w_output,
        double *b_input,
        double *b_output);
void load_image(const char *csv_path, size_t file_size,
		double **image);
double sigmoid(double d);
double sigmoid_prime(double d);
void forward(double **input,
		double **syn_input,
		double **hidden,
		double **syn_output,
		double **output);

#endif
