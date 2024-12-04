#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "../Lib/lib.h"

// Define Structs
typedef struct
{
	float lambda;
	float espilon;

	// Learning Rate
	float init_learning_rate;
	float learning_rate;
	float min_learning_rate;
	float learning_decay_rate;
	float best_loss;
	int change_iteration;
	int max_change_iteration;

	// Dropout Rate
	float init_dropout_rate;
	float dropout_rate;
	float dropout_decay_rate;
	float min_dropout_rate;

} HyperParam;

typedef struct
{
	float*** weight;	     // info->nb_layer-1 x info->nb_neuron[i+1] x info->nb_neuron[i]
	float** bias;		     // info->nb_layer-1 x info->nb_neuron[i+1]
	float*** neuron;	     // info->nb_layer x info->nb_neuron[i] x var->train_data
	float*** d_weight;       // info->nb_layer-1 x info->nb_neuron[i+1] x info->nb_neuron[i]
	float** d_bias;		     // info->nb_layer-1 x info->nb_neuron[i+1]
	float*** neuron_error; 	 // info->nb_layer-1 x info->nb_neuron[i+1] x var->train_data
	float** expected_output; // info->nb_neuron[nb_layer-1] x var->train_data
	char** result;           // 2 x var->train_data
} Param;

typedef struct
{
	float beta1;
	float beta2;
	int t;
	float*** m_weight;	// info->nb_layer-1 x info->nb_neuron[i+1] x info->nb_neuron[i]
	float** m_bias;     // info->nb_layer-1 x info->nb_neuron[i+1]
	float*** v_weight;  // info->nb_layer-1 x info->nb_neuron[i+1] x info->nb_neuron[i]
	float** v_bias;     // info->nb_layer-1 x info->nb_neuron[i+1]
} Adam;

typedef struct
{
	float*** neuron; // info->nb_layer x info->nb_neuron[i] x var->test_data
	float** result;  // info->nb_neuron[nb_layer-1] x var->test_data
} Test;

typedef struct
{
	size_t nb_layer;
	size_t* nb_neuron; // info->nb_layer
} Info;

typedef struct
{
	size_t train_data;
	size_t test_data;
	size_t batch_nb;
	unsigned int threads;
	size_t epoch;
} Var;

typedef struct
{
	HyperParam* hp; // Hyperparamter
	Param* p; // Parameter
	Adam* a; // Adam optimizer
	Test* t; // Test parameter
	Info* i; // Layer info
	Var* v; // Train info
} ANNA;

// Define Functions
int main(int argc, char** argv);
void reset_parameter(Param* param,
	Info* info);
void save_parameter(Param* param,
	Info* info);
void load_parameter(Param* param,
	Info* info);
void load_dataset(char *file_path,
        int file_nb,
        ANNA* anna);
void forward(ANNA* anna);
void backward(ANNA* anna);
void update(ANNA* anna);
void train(ANNA* anna);
void predict(ANNA* anna);
float log_loss(ANNA* anna);
void convert_char_to_output(char *c,
	size_t row,
	size_t col,
	float **output);
void convert_output_to_char(size_t nb_letter,
	size_t output_neuron,
	float **output,
	char *result);
float test(ANNA* anna);
void save_stats(size_t i,
	float log_loss,
	float train_set,
	float test_set);
void convolution(int nb_letter,
    float **input,
    float **output,
    float *filter1,
    float *filter2);
void softmax(ANNA* anna);
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
void save_hyperparameter(ANNA* anna);
void load_hyperparameter(HyperParam* hp,
    Adam* a,
    Var* v);
void reset_hyperparameter();
void reset_anna(Param* param,
	Info* info);
void reset_all();
Param* init_param(Info* info, Var* var);
Adam* init_adam(Info* info);
void load_layer(Info* info);
void free_param(Param **param, Info *info, Var* var);
#endif
