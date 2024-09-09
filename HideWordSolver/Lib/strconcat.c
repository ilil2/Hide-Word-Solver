#include "lib.h"

void strconcat(char *str1, const char *str2)
{
	size_t i = 0;
	while (str1[i])
	{
		i++;
	}

	size_t j = 0;
	while (str2[j])
	{
		str1[i+j] = str2[j];
		j++;
	}
}
