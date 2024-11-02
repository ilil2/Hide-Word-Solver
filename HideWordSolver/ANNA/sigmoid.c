#include "neural_network.h"

double sigmoid(double d)
{
	return 1/(1 + exp(-d));
}
