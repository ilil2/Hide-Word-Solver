
#include "libtest.h"
#include <stdio.h>

void test(char *func, char *test, char *correct, char *answer)
{
	printf("-----------------------------------------\n");
	printf("Test for %s(%s)\n", func, test);
	printf("Should be : %s\n", correct);
	printf("Answer    : %s\n", answer);
	printf("Correct ?   %s\n", strcomp(correct, answer) ? "Yes" : "No");
}
