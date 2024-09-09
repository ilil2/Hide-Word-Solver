#include "solver.h"
#define MAX_SIZE 500

char research_word(const char grid[MAX_SIZE][MAX_SIZE], size_t grid_size_x, size_t grid_size_y,
		const char *word, size_t word_size, int word_position[4])
{
	size_t i = 0;

	char is_find = 0;

	while (grid[i][0] && !is_find)
	{
		size_t j = 0;
		while (grid[i][j] && !is_find)
		{
			if (word[0] == grid[i][j])
			{
				char direction[2] = {};
				int start_position[2] = {i, j};
				
				if (j - word_size >= 0)
				{
					direction[0] = 0;
					direction[1] = -1;
					if (grid[i][j-1] == word[1])
					{
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}

					if (i - word_size >= 0 && grid[i-1][j-1] == word[1])
					{
						direction[0] = -1;
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}

					if (i + word_size < grid_size_y && grid[i+1][j-1] == word[1])
					{
						direction[0] = 1;
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}
				}

				if (j + word_size < grid_size_x)
				{
					direction[0] = 0;
					direction[1] = 1;
					if (grid[i][j+1] == word[1])
					{
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}

					if (i - word_size >= 0 && grid[i-1][j+1] == word[1])
					{
						direction[0] = -1;
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}

					if (i + word_size < grid_size_y && grid[i+1][j+1] == word[1])
					{
						direction[0] = 1;
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}

				}

				if (i - word_size >= 0)
				{
					direction[0] = -1;
					direction[1] = 0;
					if (grid[i-1][j] == word[1])
					{
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}
				}

				if (i + word_size < grid_size_y)
				{
					direction[0] = 1;
					direction[1] = 0;
					if (grid[i+1][j] == word[1])
					{
						is_find += research_word_with_direction(grid, word, word_position, start_position, direction);
					}
				}
			}

			j += 1;
		}
		i += 1;
	}

	if(is_find)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
