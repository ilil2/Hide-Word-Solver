#include "neural_network.h"

void save_grid(char* path, size_t grid_width,
	size_t grid_height, char* result)
{
    FILE* grid_file = NULL;

    grid_file = fopen(path, "w");

    if (grid_file == NULL)
    {
        create_file(path);
        grid_file = fopen(path, "w");
    }
    
    if (grid_file != NULL)
    {  
        for (size_t i = 0; i < grid_height; i++)
        {
            for (size_t j = 0; j < grid_width; j++)
            {
                fprintf(grid_file, "%c", result[grid_width * i + j]);
            }
        	fprintf(grid_file, "\n");
        }
    }
    else
    {
        err(1, "fopen()");
    }

    fclose(grid_file);
}