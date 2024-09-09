#include "lib.h"
#include <stddef.h>

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
