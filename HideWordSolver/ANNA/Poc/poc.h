#ifndef __POC_H__
#define __POC_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <time.h>
#include "../../Lib/lib.h"

#define input_neuron 2
#define hidden_neuron 3
#define output_neuron 1
#define nb_letters 4

int main();
float sigmoid(float d);
float sigmoid_prime(float d);
void forward(int nb_letter,
		float **input,
		float **hidden,
		float **output,
		float **w_input,
		float **w_output,
		float *b_input,
		float *b_output);
void backward(int nb_letter,
		float **w_output,
		float **input,
		float **hidden,
		float **output,
		float **expected_output,
		float **output_error,
		float **dw_output,
		float *db_output,
		float **hidden_error,
		float **dw_input,
		float *db_input);
void update(float **w_input,
		float **w_output,
		float *b_input,
		float *b_output,
		float **dw_output,
		float *db_output,
		float **dw_input,
		float *db_input,
        float learning_rate);
void train(int nb_letter,
		char *anna_result,
		float** w_input,
		float** w_output,
		float* b_input,
		float* b_output);
float log_loss(int nb_letter,
        float **expected_output,
        float **output);
void poc_matrix_product_t(size_t row1, size_t col1, float **mat1,
        size_t row2, size_t col2, float **mat2, float **res,
		char trans_nbr);
void poc_matrix_product(size_t row1, size_t col1, float **mat1,
		size_t row2, size_t col2, float **mat2, float **res);

#endif