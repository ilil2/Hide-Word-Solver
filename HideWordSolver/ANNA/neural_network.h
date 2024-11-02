#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "../Lib/lib.h"

#define image_size 32
#define filter_size 3
#define input_neuron 256
#define hidden_neuron1 512
#define hidden_neuron2 256
#define output_neuron 26
#define nb_dataset 1

int main(int argc, char** argv);
void reset_parameter(double **w_input,
	double **w_hidden,
	double **w_output,
	double *b_input,
	double *b_hidden,
	double *b_output);
void save_parameter(double **w_input,
	double **w_hidden,
	double **w_output,
	double *b_input,
	double *b_hidden,
	double *b_output);
void load_parameter(double **w_input,
	double **w_hidden,
	double **w_output,
	double *b_input,
	double *b_hidden,
	double *b_output);
void load_image(char *file_path,
	int file_nb,
        size_t file_size,
        double **input,
        double **output);
void forward(int nb_letter,
	double **input,
        double **hidden1,
        double **hidden2,
        double **output,
        double **w_input,
        double **w_hidden,
        double **w_output,
        double *b_input,
        double *b_hidden,
        double *b_output,
	double dropout_rate,
	char threads);
void backward(int nb_letter,
        double **w_output,
        double **w_hidden,
        double **input,
        double **hidden1,
        double **hidden2,
        double **output,
        double **expected_output,
        double **output_error,
        double **dw_output,
        double *db_output,
        double **hidden2_error,
        double **dw_hidden,
        double *db_hidden,
        double **hidden1_error,
        double **dw_input,
        double *db_input,
	char threads);
void update(double **w_input,
        double **w_hidden,
        double **w_output,
        double *b_input,
        double *b_hidden,
        double *b_output,
        double **dw_output,
        double *db_output,
        double **dw_hidden,
        double *db_hidden,
        double **dw_input,
        double *db_input,
        double **m_w_input,
        double **v_w_input,
        double **m_w_hidden,
        double **v_w_hidden,
        double **m_w_output,
        double **v_w_output,
        double *m_b_input,
        double *v_b_input,
        double *m_b_hidden,
        double *v_b_hidden,
        double *m_b_output,
        double *v_b_output,
        double learning_rate,
        double beta1,
        double beta2,
        double epsilon,
        int t);
void train(int nb_letter,
	char *anna_result,
	double** w_input,
	double** w_hidden,
	double** w_output,
	double* b_input,
	double* b_hidden,
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
	double *b_output,
	double threads);
double log_loss(int nb_letter,
        double **expected_output,
        double **output);
void convert_char_to_output(char *c,
	size_t row,
	size_t col,
	double **output);
void convert_output_to_char(int nb_letter,
	double **output,
	char *anna_result);
double test(size_t test_size,
	double **test_input,
	double **test_hidden1,
	double **test_hidden2,
	double **test_expected,
	double **test_output,
	double **w_input,
	double **w_hidden,
	double **w_output,
	double *b_input,
	double *b_hidden,
	double *b_output,
	char thread_nbr);
void save_stats(size_t i,
	double log_loss,
	double train_set,
	double test_set);
void convolution(int nb_letter,
        double **input,
        double **output,
        double *filter1,
        double *filter2);
void softmax(int nb_letter,
	double **output);
double relu(double d);
double relu_prime(double d);
double sigmoid(double d);
double sigmoid_prime(double d);
double activ(double d);
double activ_prime(double d);
void pooling(size_t nb_letter,
	double **input,
	size_t output_size,
	double **output);
void layers(size_t nb_letter,
	double **input,
	double **output);

#endif
