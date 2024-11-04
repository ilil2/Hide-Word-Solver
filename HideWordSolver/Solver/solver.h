#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <stddef.h>
#include <stdio.h>

#define MAX_SIZE 100

int main(int argc, char** argv);

char research_word(const char grid[MAX_SIZE][MAX_SIZE], int grid_size_x,
	int grid_size_y, const char *word, int word_size,
	int word_position[4]);

char research_word_with_direction(const char grid[MAX_SIZE][MAX_SIZE],
		const char *word, int word_position[4], const int start_position[2],
		const char direction[2]);

#endif
