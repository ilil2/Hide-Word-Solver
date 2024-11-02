#include <err.h>
#include "solver.h"
#include "../Lib/lib.h"

// Search for a word in a letter grid
// The first argument is the file containing the grid, and the second is the word to search for.
int main(int argc, char** argv)
{
	if(argc != 3)
	{
		errx(400, "The number of arguments is invalid.");
	}

	FILE* file = NULL;

	file = fopen(argv[1], "r");

	if(file != NULL)
	{
		char file_content[MAX_SIZE][MAX_SIZE] = {};

		char is_word_find = 0;
		int word_position[4] = {0, 0, 0, 0};

		fgets(file_content[0], MAX_SIZE, file);

		size_t i = 1;

		// Get the grid in the file
		while (file_content[i - 1][0] != 0)
		{
			fgets(file_content[i], MAX_SIZE, file);
			i += 1;
		}

		fclose(file);

		to_upper(argv[2]);

		// Research the word in the grid
		is_word_find = research_word(file_content, strlen(file_content[0]),
				i, argv[2], strlen(argv[2]), word_position);

		// Print word position
		if(is_word_find)
		{
			printf("(%i,%i)(%i,%i)", word_position[1], word_position[0],
					word_position[3], word_position[2]);
		}
		else
		{
			printf("Not found");
		}
	}
	else
	{
		errx(404, "The file is not found.");
	}

	return 0;
}
