#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(double **array, double **array2, int n) {
    srand(time(NULL));

    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        double *temp = array[i];
		double *temp2 = array2[i];

        array[i] = array[j];
        array[j] = temp;

		array2[i] = array2[j];
		array2[j] = temp2;
    }
}
