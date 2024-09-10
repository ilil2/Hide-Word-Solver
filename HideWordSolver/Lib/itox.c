#include "lib.h"

void itox(int i, char *hexa)
{
	size_t l = intlen(i);
	hexa[l] = 0;
	l--;

	while (l)
	{
		int temp = i % 16;
		i /= 16;

		switch (temp)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 6:
			case 7:
			case 8:
			case 9:
				hexa[l] = itoc(temp);
			case 10:
				hexa[l] = 'a';
			case 11:
				hexa[l] = 'b';
			case 12:
				hexa[l] = 'c';
			case 13:
				hexa[l] = 'd';
			case 14:
				hexa[l] = 'e';
			case 15:
				hexa[l] = 'f';
		}

		l--;
	}
}
