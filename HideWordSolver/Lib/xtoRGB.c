#include "lib.h"
#include "err.h"

// Convert hexa to rgb
void xtoRGB(const char hexa[6], int rgb[3])
{
	rgb[0] = 0; rgb[1] = 0; rgb[2] = 0;

	for (size_t i = 0; i < 6; i += 2)
	{
		if(hexa[i] >= 'a' && hexa[i] <= 'f')
		{
			rgb[i/2] += (hexa[i] - 'a' + 10) * 16;
		}
		else if(hexa[i] >= '0' && hexa[i] <= '9')
		{
			rgb[i/2] += (hexa[i] - '0') * 16;
		}
		else
		{
			errx(12, "Invalid hexadecimal number.");
		}
		
		if(hexa[i+1] >= 'a' && hexa[i+1] <= 'f')
		{
			rgb[i/2] += hexa[i+1] - 'a' + 10;
		}
		else if(hexa[i+1] >= '0' && hexa[i+1] <= '9')
		{
			rgb[i/2] += hexa[i+1] - '0';
		}
		else
		{
			errx(12, "Invalid hexadecimal number.");
		}
	}
}
