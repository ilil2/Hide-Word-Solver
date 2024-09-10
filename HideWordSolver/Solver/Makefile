# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = solver.c research_word.c research_word_with_direction.c
LIB_SRC = ../Lib/to_upper.c ../Lib/char_to_upper.c ../Lib/strlen.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = solver

# Règle pour générer l'exécutable
$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

# Règle générique pour compiler les fichiers .o à partir des .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle clean pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -rf $(OBJ) $(EXE)
