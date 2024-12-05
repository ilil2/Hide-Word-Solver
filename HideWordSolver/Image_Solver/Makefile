# Makefile

CC=gcc
CFLAGS=-Wall -Wextra -lSDL2 -lSDL2_image -fsanitize=address -O3
SRC=main.c draw.c
OBJ=$(SRC:.c=.o)
EXE=draw

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(CFLAGS) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(EXE)
