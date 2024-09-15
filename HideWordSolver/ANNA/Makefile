# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g 
SRC = neural_network.c reset_parameter.c save_parameter.c load_parameter.c load_image.c sigmoid.c sigmoid_prime.c train.c forward.c backward.c convert_char_to_output.c convert_output_to_char.c
LIB_SRC = ../Lib/matrix_product.c ../Lib/matrix_addition.c ../Lib/matrix_transpose.c ../Lib/strcomp.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = ANNA

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)