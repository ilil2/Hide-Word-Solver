#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Shuffle a matrix
void matrix_shuffle(float **array, float **array2, int rows1, int rows2,
    int cols)
{
    for (int i = cols - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        for (int k = 0; k < rows1; k++)
        {
            float temp1 = array[k][i];
            array[k][i] = array[k][j];
            array[k][j] = temp1;
        }

        for (int k = 0; k < rows2; k++)
        {
            float temp2 = array2[k][i];
            array2[k][i] = array2[k][j];
            array2[k][j] = temp2;
        }
    }
}
