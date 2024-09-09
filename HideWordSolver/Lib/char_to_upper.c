#include "lib.h"

char char_to_upper(char c)
{
	if (c < 'z' || c > 'a')
	{
		return c - 32;
	}
	return c;
}
