# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -lSDL2
SRC = main_dataset.c add_to_dataset.c bmp_to_csv.c 
OBJ = $(SRC:.c=.o)
EXE = add_data

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
