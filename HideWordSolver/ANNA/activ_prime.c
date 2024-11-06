#include "neural_network.h"

float activ_prime(float d)
{
    return relu_prime(d);
}