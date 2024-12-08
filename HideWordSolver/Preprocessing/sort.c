#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Function to swap two elements
void swap(Uint32* a, Uint32* b)
{
    Uint32 t = *a;
    *a = *b;
    *b = t;
}

int partition(Uint32 arr[], int low, int high)
{
  
    // Choose the pivot
    Uint32 pivot = arr[high];
  
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements on the left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++)
	{
        if (arr[j] < pivot)
		{
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// The QuickSort function implementation
void quickSort(Uint32 arr[], int low, int high)
{
  
    if (low < high)
	{  
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
