#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <stdio.h>
#include <stddef.h>

#define input_neuron 1024
#define hidden_neuron 256
#define output_neuron 5

int main(int argc, char** argv);
void save(double w_input[input_neuron][hidden_neuron],
		double w_output[hidden_neuron][output_neuron],
		double b_input[hidden_neuron],
		double b_output[output_neuron]);
void load(double w_input[input_neuron][hidden_neuron],
		double w_output[hidden_neuron][output_neuron],
        double b_input[hidden_neuron],
        double b_output[output_neuron]);
double sigmoid(double d);
double sigmoid_prime(double d);
void forward(double input[1][input_neuron],
		double syn_input[input_neuron][hidden_neuron],
		double syn_output[hidden_neuron][output_neuron],
		double output[output_neuron][1]);

#endif
