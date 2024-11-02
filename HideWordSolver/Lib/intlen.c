#include "lib.h"
#include <stddef.h>

// Return the len of int
size_t intlen(int i)
{
	size_t len = 0;
	while (i)
	{
		len++;
		i /= 10;
	}
	return len;
}
