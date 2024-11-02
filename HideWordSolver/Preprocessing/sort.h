#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>

void swap(Uint32* a, Uint32* b);

Uint32 partition(Uint32 arr[], Uint32 low, Uint32 high);

void quickSort(Uint32 arr[], Uint32 low, Uint32 high);

#endif
