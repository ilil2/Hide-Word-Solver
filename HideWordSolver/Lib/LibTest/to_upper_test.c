#include "libtest.h"

void to_upper_test()
{
	char* name = "to_upper";
    char* tests[] = {"aA", "Hello world!", "HELLO WORLD!"};
    char* res[] = {"AA", "HELLO WORLD!", "HELLO WORLD!"};

    for (size_t i = 0; i < 3; i++)
    {
		char dest[21] = {};
		strcopy(dest, tests[i]);
		to_upper(dest);
        test(name, tests[i], res[i], dest);
    }
}
