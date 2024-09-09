#include "lib.h"
#include <stddef.h>

void itoa(int i, char *str)
{
	size_t len = intlen(i);
	str[len] = 0;

	while (i)
	{
		str[len-1] = itoc(i%10);
		i /= 10;
		len--;
	}
}
