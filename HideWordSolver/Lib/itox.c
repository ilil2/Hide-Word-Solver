#include "lib.h"

// Convert int to string (hexa)
void itox(int i, char *hexa)
{
	size_t l = 5;
	hexa[6] = 0;

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
				break;
			case 10:
				hexa[l] = 'a';
				break;
			case 11:
				hexa[l] = 'b';
				break;
			case 12:
				hexa[l] = 'c';
				break;
			case 13:
				hexa[l] = 'd';
				break;
			case 14:
				hexa[l] = 'e';
				break;
			case 15:
				hexa[l] = 'f';
				break;
		}

		l--;
	}
}
