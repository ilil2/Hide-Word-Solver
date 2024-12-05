#include "neural_network.h"

void save_word(char* path, size_t word_size, char* result)
{
    FILE* word_file = NULL;

    word_file = fopen(path, "a");

    if (word_file == NULL)
    {
        create_file(path);
        word_file = fopen(path, "a");
    }
    
    if (word_file != NULL)
    {  
        for (size_t i = 0; i < word_size; i++)
        {
            fprintf(word_file, "%c", result[i]);
        }
        fprintf(word_file, "\n");
    }
    else
    {
        err(1, "fopen()");
    }

    fclose(word_file);
}