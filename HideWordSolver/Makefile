# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags --libs gtk+-3.0` -lSDL2 -lSDL2_image -lm -fsanitize=address
SRC = main.c on_start_button_pressed.c make_signals.c next_solver.c sdl_surface_to_pixbuf.c on_spinbutton_value_changed.c
PREPROSS_SRC = Preprocessing/grayscale.c Preprocessing/binarization.c Preprocessing/medianfilter.c Preprocessing/sort.c Preprocessing/extraction.c
ROTATE_SRC = Rotate/auto_rotation.c Rotate/rotation_detection.c Rotate/sobel.c Rotate/display.c Rotate/save.c
LIB_SRC = 
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o) $(PREPROSS_SRC:.c=.o) $(ROTATE_SRC:.c=.o)
EXE = ANNA-Solver-IA

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE) *.png
