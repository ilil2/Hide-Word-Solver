#include "libtest.h"

void itoc_test()
{
	char* name = "itoc";
    int tests[] = {1, 5, 4};
    char res[] = {'1', '5', '4'};

    for (size_t i = 0; i < 3; i++)
    {
		char r[5] = {};
		ctoa(res[i],r);

        char a[42] = {};
        ctoa(itoc(tests[i]),a);

		char t[5] = {};
		ctoa(tests[i],t);
		
        test(name, t, r, a);
    }
}
