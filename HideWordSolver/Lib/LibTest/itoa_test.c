#include "libtest.h"

void itoa_test()
{
	char* name = "char_to_upper";
    int tests[] = {1, 124, 42};
    char* res[] = {"1", "124", "42"};

    for (size_t i = 0; i < 3; i++)
    {
        char a[5] = {};
        itoa(tests[i],a);

        char t[5] = {};
        itoa(tests[i],t);

        test(name, t, res[i], a);
    }

}
