#include "libtest.h"
//#include "../lib.h"

void strlen_test()
{
	char* name = "strlen";
	char* tests[] = {"test", "test.", "42"};
	int res[] = {4, 5, 2};

	for (size_t i = 0; i < 3; i++)
	{
		char r[5] = {};
		itoa(res[i], r);
		char t[42] = {};
		itoa(strlen(tests[i]),t);
		test(name, tests[i], r, t);
	}
}
