#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include "../Lib/lib.h"

#define image_size 32
#define filter_size 3
#define input_neuron 1024
#define hidden_neuron 256
#define output_neuron 26
#define nb_dataset 32

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
void load_image(char *file_path,
		int file_nb,
        size_t file_size,
        double **input,
        double **output);
double sigmoid(double d);
double sigmoid_prime(double d);
void forward(int nb_letter,
		double **input,
		double **hidden,
		double **output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output,
		char threads);
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
		double *db_input,
		char threads);
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
		double* b_output,
		char threads);
void predict(int nb_letter,
		char *anna_result,
		double **input,
        double **hidden,
		double **output,
		double **w_input,
		double **w_output,
		double *b_input,
		double *b_output);
double log_loss(int nb_letter,
        double **expected_output,
        double **output);
void convert_char_to_output(char *c, size_t row, size_t col, double **output);
void convert_output_to_char(int nb_letter, double **output, char *anna_result);
double test(size_t test_size, double **test_input, double **hidden,
        double **expected, double **output, double **w_input,
    	double **w_output,double *b_input, double *b_output,
		char thread_nbr);
void save_stats(size_t i, double log_loss, double train_set, double test_set);
void convolution(int nb_letter,
        double **input,
        double **output,
        double *filter1,
        double *filter2);
double relu(double d);
double activ(double d);
void pooling(size_t nb_letter, double **input, size_t output_size,
		double **output);
void layers(size_t nb_letter, double **input, size_t output_size,
		double **output);

#endif
