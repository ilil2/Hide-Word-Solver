#include "lib.h"

// Convert string to int
int atoi(const char *str)
{
	int res = 0;
	size_t i = 0;

	while(str[i])
	{
		res = res * 10 + str[i] - '0';
		i += 1;
	}

	return res;
}
