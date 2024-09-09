#include "libtest.h"

void intlen_test()
{
	char* name = "intlen";
    int tests[] = {123, 5, 42};
    int res[] = {3, 1, 2};

    for (size_t i = 0; i < 3; i++)
    {
        char r[5] = {};
        itoa(res[i],r);

        char a[42] = {};
        itoa((int)intlen(tests[i]),a);

        char t[5] = {};
        itoa(tests[i],t);

        test(name, t, r, a);
    }
}
