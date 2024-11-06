#include <math.h>

float sigmoid_prime(float d)
{
	return d * (1-d);
}
