#include "lib.h"
#include <stddef.h>

// Capitalize a string
void to_upper(char *str)
{
	size_t i = 0;
	while (str[i])
	{
		str[i] = char_to_upper(str[i]);
		i++;
	}
}
