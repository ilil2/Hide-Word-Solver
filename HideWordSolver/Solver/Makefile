# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = solver.c research_word.c research_word_with_direction.c
LIB_SRC = ../Lib/to_upper.c ../Lib/char_to_upper.c ../Lib/strlen.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = solver

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
