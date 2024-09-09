#include "lib.h"
#include "LibTest/libtest.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	for (size_t i = 1; (int)i < argc; i++)
	{
		if (strcomp(argv[i], "strlen"))
		{
			strlen_test();
		}
		else if (strcomp(argv[i], "strcomp"))
		{
			strcomp_test();
		}
		else if (strcomp(argv[i], "itoc"))
		{
			itoc_test();
		}
		else if (strcomp(argv[i], "intlen"))
		{
			intlen_test();
		}
		else if (strcomp(argv[i], "char_to_upper"))
		{
			char_to_upper_test();
		}
		else if (strcomp(argv[i], "to_upper"))
		{
			to_upper_test();
		}
		else if (strcomp(argv[i], "itoa"))
		{
			itoa_test();
		}
		else if (strcomp(argv[i], "ctoa"))
		{
			ctoa_test();
		}
		else if (strcomp(argv[i], "strconcat"))
		{
			strconcat_test();
		}
		else if (strcomp(argv[i], "strcopy"))
		{
			strcopy_test();
		}		
		else
		{
			strcomp_test();
		}
	}
}
