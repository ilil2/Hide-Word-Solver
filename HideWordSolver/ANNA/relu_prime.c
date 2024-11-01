#include "neural_network.h"

double relu_prime(double d)
{
    return d > 0 ? 1.0 : 0.0;
}