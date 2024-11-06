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
#define nb_dataset 23

// Define Structs
typedef struct
{
	float learning_rate;
	float lambda;
	float espilon;
	float dropout_rate;
} HyperParam;

typedef struct
{
	float*** weight;
	float** bias;
	float*** neuron;
	float*** d_weight;
	float** d_bias;
	float*** neuron_error;
	float** expected_output;
	float** result;
} Param;

typedef struct
{
	float beta1;
	float beta2;
	int t;
	float*** m_weight;
	float** m_bias;
	float*** v_weight;
	float** v_bias;
} Adam;

typedef struct
{
	float*** neuron;
	float** result;
} Test;

typedef struct
{
	size_t nb_layer;
	size_t* nb_neuron;
} Info;

typedef struct
{
	size_t train_data;
	size_t test_data;
	size_t batch_size;
	unsigned int threads;
	size_t epoch;
} Var;

typedef struct
{
	HyperParam* hp;
	Param* p;
	Adam* a;
	Test* t;
	Info* i;
	Var* v;
} ANNA;

// Define Functions
int main(int argc, char** argv);
void reset_parameter(float **w_input,
	float **w_hidden,
	float **w_output,
	float *b_input,
	float *b_hidden,
	float *b_output);
void save_parameter(float **w_input,
	float **w_hidden,
	float **w_output,
	float *b_input,
	float *b_hidden,
	float *b_output);
void load_parameter(float **w_input,
	float **w_hidden,
	float **w_output,
	float *b_input,
	float *b_hidden,
	float *b_output);
void load_image(char *file_path,
	int file_nb,
        size_t file_size,
        float **input,
        float **output);
void forward(int nb_letter,
	float **input,
        float **hidden1,
        float **hidden2,
        float **output,
        float **w_input,
        float **w_hidden,
        float **w_output,
        float *b_input,
        float *b_hidden,
        float *b_output,
	float dropout_rate,
	int threads);
void backward(int nb_letter,
        float **w_output,
        float **w_hidden,
        float **input,
        float **hidden1,
        float **hidden2,
        float **output,
        float **expected_output,
        float **output_error,
        float **dw_output,
        float *db_output,
        float **hidden2_error,
        float **dw_hidden,
        float *db_hidden,
        float **hidden1_error,
        float **dw_input,
        float *db_input,
	int threads);
void update(float **w_input,
        float **w_hidden,
        float **w_output,
        float *b_input,
        float *b_hidden,
        float *b_output,
        float **dw_output,
        float *db_output,
        float **dw_hidden,
        float *db_hidden,
        float **dw_input,
        float *db_input,
        float **m_w_input,
        float **v_w_input,
        float **m_w_hidden,
        float **v_w_hidden,
        float **m_w_output,
        float **v_w_output,
        float *m_b_input,
        float *v_b_input,
        float *m_b_hidden,
        float *v_b_hidden,
        float *m_b_output,
        float *v_b_output,
        float learning_rate,
        float beta1,
        float beta2,
        float epsilon,
        float lambda,
        int t);
void train(int nb_letter,
	char *anna_result,
	float** w_input,
	float** w_hidden,
	float** w_output,
	float* b_input,
	float* b_hidden,
	float* b_output,
	int threads);
void predict(int nb_letter,
	char *anna_result,
	float **input,
        float **hidden,
	float **output,
	float **w_input,
	float **w_output,
	float *b_input,
	float *b_output,
	float threads);
float log_loss(int nb_letter,
        float **expected_output,
        float **output);
void convert_char_to_output(char *c,
	size_t row,
	size_t col,
	float **output);
void convert_output_to_char(int nb_letter,
	float **output,
	char *anna_result);
float test(size_t test_size,
	float **test_input,
	float **test_hidden1,
	float **test_hidden2,
	float **test_expected,
	float **test_output,
	float **w_input,
	float **w_hidden,
	float **w_output,
	float *b_input,
	float *b_hidden,
	float *b_output,
	int thread_nbr);
void save_stats(size_t i,
	float log_loss,
	float train_set,
	float test_set);
void convolution(int nb_letter,
        float **input,
        float **output,
        float *filter1,
        float *filter2);
void softmax(int nb_letter,
	float **output);
float relu(float d);
float relu_prime(float d);
float sigmoid(float d);
float sigmoid_prime(float d);
float activ(float d);
float activ_prime(float d);
void pooling(size_t nb_letter,
	float **input,
	size_t output_size,
	float **output);
void layers(size_t nb_letter,
	float **input,
	float **output);

#endif
