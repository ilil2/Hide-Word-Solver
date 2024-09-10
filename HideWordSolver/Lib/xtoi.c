#include "lib.h"
#include <err.h>

int xtoi(const char *hexa)
{
	int res = 0;
	size_t i = 0;

	while (hexa[i])
	{
		res *= 16;
		if(hexa[i] >= 'a' && hexa[i] <= 'f')
		{
			res += hexa[i] - 'a' + 10;
		}
		else if(hexa[i] >= '0' && hexa[i] <= '9')
		{
			res += hexa[i] - '0';
		}
		else
		{
			errx(12, "Invalid hexadecimal number.");
		}

		i += 1;
	}

	return res;
}
