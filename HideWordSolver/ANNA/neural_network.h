#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include "../Lib/lib.h"

#define input_neuron 1024
#define hidden_neuron 256
#define output_neuron 26

int main(int argc, char** argv);
void reset_parameter(double **w_input,
		double **w_output,
		double *b_input,
		double *b_output);
void save_parameter(double **w_input,
		double **w_output,
		double *b_input,
		double *b_output);
void load_parameter(double **w_input,
		double **w_output,
        double *b_input,
        double *b_output);
void load_image(const char *csv_path, size_t file_size,
		double **image);
double sigmoid(double d);
double sigmoid_prime(double d);
void forward(double *input,
		double *hidden,
		double *output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output);
void backward(double **w_output,
		double *input,
		double *hidden,
		double *output,
		double *expected_output,
		double *output_error,
		double **dw_output,
		double *db_output,
		double *hidden_error,
		double **dw_input,
		double *db_input);
void update(double **w_input,
		double **w_output,
		double *b_input,
		double *b_output,
		double **dw_output,
		double *db_output,
		double **dw_input,
		double *db_input,
        double learning_rate);
void train(int letter_nb,
		double** syn_input,
		double** syn_output,
		double* b_input,
		double* b_output);
char predict(double *input, double *output);
void convert_char_to_output(char c, size_t size, double *output);
char convert_output_to_char(double *output);

#endif
