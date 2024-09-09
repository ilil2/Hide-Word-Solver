#include "libtest.h"

void strconcat_test()
{
	char* name = "char_to_upper";

	char test1[5] = "a";
	char test2[5] = "4";
	char test3[20] = "Hello ";

    char* tests1[] = {test1, test2, test3};
	char* tests2[] = {"A", "2", "world!"};
    char* res[] = {"aA", "42", "Hello world!"};

    for (size_t i = 0; i < 3; i++)
    {
        char a[42] = {};
		strcopy(a, tests1[i]);
        strconcat(a, tests2[i]);

        char t[42] = {};
		strconcat(t, tests1[i]);
        strconcat(t, ", ");
		strconcat(t, tests2[i]);

        test(name, t, res[i], a);
    }

}
