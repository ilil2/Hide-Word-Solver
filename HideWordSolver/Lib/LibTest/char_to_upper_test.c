#include "libtest.h"

void char_to_upper_test()
{
	char* name = "char_to_upper";
    char tests[] = {'a', ';', 'A'};
    char res[] = {'A', ';', 'A'};

    for (size_t i = 0; i < 3; i++)
    {
        char r[5] = {};
        ctoa(res[i],r);

        char a[42] = {};
        ctoa(char_to_upper(tests[i]),a);

        char t[5] = {};
        ctoa(tests[i],t);

        test(name, t, r, a);
    }

}
