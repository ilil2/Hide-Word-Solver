#include "lib.h"
#include <stddef.h>

char strcomp(const char *str1, const char *str2)
{
	size_t i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			return 0;
		}
		i++;
	}

	return str1[i] == str2[i];
}
