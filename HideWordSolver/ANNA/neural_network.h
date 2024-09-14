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
void reset_parameter(double w_input[input_neuron][hidden_neuron],
		    double w_output[hidden_neuron][output_neuron],
		    double b_input[hidden_neuron],
		    double b_output[output_neuron]);
void save_parameter(const double w_input[input_neuron][hidden_neuron],
		const double w_output[hidden_neuron][output_neuron],
		const double b_input[hidden_neuron],
		const double b_output[output_neuron]);
void load_parameter(double w_input[input_neuron][hidden_neuron],
		double w_output[hidden_neuron][output_neuron],
        double b_input[hidden_neuron],
        double b_output[output_neuron]);
void load_image(const char *image_path, size_t file_size,
		double image[file_size][input_neuron]);
double sigmoid(double d);
double sigmoid_prime(double d);
void forward(double input[1][input_neuron],
		double syn_input[input_neuron][hidden_neuron],
		double hidden[1][hidden_neuron],
		double syn_output[hidden_neuron][output_neuron],
		double output[1][output_neuron]);

#endif
