# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = char_to_upper.c intlen.c itoa.c itoc.c strcomp.c strlen.c to_upper.c main.c strconcat.c ctoa.c strcopy.c itox.c xtoRGB.c xtoi.c
TEST_SRC = LibTest/strlen_test.c LibTest/test.c LibTest/strcomp_test.c LibTest/itoc_test.c LibTest/intlen_test.c LibTest/char_to_upper_test.c LibTest/to_upper_test.c LibTest/itoa_test.c LibTest/ctoa_test.c LibTest/strconcat_test.c LibTest/strcopy_test.c
OBJ = $(SRC:.c=.o) $(TEST_SRC:.c=.o)
EXE = test

# Règle pour générer l'exécutable
$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

# Règle générique pour compiler les fichiers .o à partir des .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle clean pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -rf $(OBJ) $(EXE)

