#include <math.h>

float sigmoid(float d)
{
	return 1/(1 + exp(-d));
}
