#include "solver.h"

char research_word_with_direction(
		const char grid[MAX_SIZE][MAX_SIZE],
		const char *word,
		int word_position[4],
		const int start_position[2],
		const char direction[2])
{
	size_t i = 0;
	int position[2] = {start_position[0], start_position[1]};

	while (word[i] && word[i] == grid[position[0]][position[1]])
	{
		position[0] += direction[0];
		position[1] += direction[1];
		i += 1;
	}

	if(!word[i])
	{
		word_position[0] = start_position[0];
		word_position[1] = start_position[1];
		word_position[2] = position[0] - direction[0];
		word_position[3] = position[1] - direction[1];
		return 1;
	}
	else
	{
		return 0;
	}
}
