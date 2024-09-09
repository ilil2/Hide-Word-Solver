#include "libtest.h"

void strcopy_test()
{
	char* name = "char_to_upper";
    char* tests[] = {"A", "42", "Hw!"};
    char res[][5] = {"", "A", ""};

    for (size_t i = 0; i < 3; i++)
    {
		strcopy(res[i], tests[i]);
        test(name, tests[i], tests[i], res[i]);
    }

}
