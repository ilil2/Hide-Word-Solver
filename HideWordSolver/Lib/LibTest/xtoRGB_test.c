#include "libtest.c"

void xtoRGB_test()
{
	char* name = "xtoRGB";
    char* tests[] = {"111111", "ffffff", "0001fe"};
    int res[][3] = 
	{
		{17, 17, 17},
		{254, 254, 254},
		{0, 1, 253}
	};

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
