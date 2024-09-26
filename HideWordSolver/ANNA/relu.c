#include "neural_network.h"

double relu(double d)
{
    return max(0, d);
}