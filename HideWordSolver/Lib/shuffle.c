#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(char array[], int n) {
    srand(time(NULL));

    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        char temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}