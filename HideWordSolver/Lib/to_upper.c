#include "lib.h"
#include <stddef.h>

void to_upper(char *str)
{
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++)
	{
		str[i] = char_to_upper(str[i]);
	}
}
