#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_shuffle(double **array, double **array2, int rows, int cols) {
    srand(time(NULL));

    for (int i = cols - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        for (int k = 0; k < rows; k++)
        {
            double temp1 = array[k][i];
            array[k][i] = array[k][j];
            array[k][j] = temp1;

            double temp2 = array2[k][i];
            array2[k][i] = array2[k][j];
            array2[k][j] = temp2;
        }
    }
}