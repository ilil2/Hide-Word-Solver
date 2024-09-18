# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags --libs gtk+-3.0`
SRC = main.c on_start_button_pressed.c make_signals.c next_solver.c
LIB_SRC = 
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = ANNA-Solver-IA

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
