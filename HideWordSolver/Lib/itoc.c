#include "lib.h"

// Convert int to char
char itoc(char i)
{
	if (i < 10 && i >= 0)
	{
		return i + 48;
	}
	return i;
}
