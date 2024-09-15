#include <math.h>

double sigmoid_prime(double d)
{
	return d * (1-d);
}
