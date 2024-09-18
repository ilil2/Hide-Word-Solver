#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include "../../Lib/lib.h"

#define input_neuron 2
#define hidden_neuron 3
#define output_neuron 1
#define nb_letters 4

int main();
double sigmoid(double d);
double sigmoid_prime(double d);
void forward(int nb_letter,
		double **input,
		double **hidden,
		double **output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output);
void backward(int nb_letter,
		double **w_output,
		double **input,
		double **hidden,
		double **output,
		double **expected_output,
		double **output_error,
		double **dw_output,
		double *db_output,
		double **hidden_error,
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
void train(int nb_letter,
		char *anna_result,
		double** w_input,
		double** w_output,
		double* b_input,
		double* b_output);
double log_loss(int nb_letter,
        double **expected_output,
        double **output);

#endif