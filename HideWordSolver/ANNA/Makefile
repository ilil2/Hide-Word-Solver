# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g 
SRC = neural_network.c reset_parameter.c save_parameter.c load_parameter.c load_image.c sigmoid.c sigmoid_prime.c forward.c
LIB_SRC = ../Lib/matrix_product.c ../Lib/strcomp.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = ANNA

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
