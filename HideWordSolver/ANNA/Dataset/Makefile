# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g -O3 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lSDL2
SRC = main_dataset.c add_to_dataset.c bmp_to_csv.c ../../Lib/atoi.c
OBJ = $(SRC:.c=.o)
EXE = add_data

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
