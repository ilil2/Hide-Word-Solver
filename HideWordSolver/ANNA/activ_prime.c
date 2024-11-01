#include "neural_network.h"

double activ_prime(double d)
{
    return relu_prime(d);
}