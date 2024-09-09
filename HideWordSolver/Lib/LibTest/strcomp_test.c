#include "libtest.h"

void strcomp_test()
{
		char* name = "strcomp";
        char* tests1[] = {"test", "test.", "42"};
		char* tests2[] = {"test", "test", "42"};
        int res[] = {1, 0, 1};

        for (size_t i = 0; i < 3; i++)
        {
                char r[5] = {};
                itoa(res[i], r);
                char t[5] = {};
                itoa(strcomp(tests1[i], tests2[i]),t);

				char str[42] = {};
				strconcat(str, tests1[i]);
				strconcat(str, ", ");
				strconcat(str, tests2[i]);

                test(name, str, r, t);
        }
}
