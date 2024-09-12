# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lSDL2
SRC = main.c get_RGB.c
LIB = ../Lib/itox.c ../Lib/xtoRGB.c ../Lib/intlen.c ../Lib/itoc.c
OBJ = $(SRC:.c=.o) $(LIB:.c=.o)
EXE = Prepross

# Règle pour générer l'exécutable
$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

# Règle générique pour compiler les fichiers .o à partir des .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle clean pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -rf $(OBJ) $(EXE)

