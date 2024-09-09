#include "libtest.h"

void ctoa_test()
{
	char* name = "char_to_upper";
    char tests[] = {'a', ';', 'A'};
    char* res[] = {"a", ";", "A"};

    for (size_t i = 0; i < 3; i++)
    {
        char a[42] = {};
        ctoa(tests[i],a);

        char t[5] = {};
        ctoa(tests[i],t);

        test(name, t, res[i], a);
    }

}
