# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g -lm
SRC = ../sigmoid.c ../sigmoid_prime.c poc_train.c forward.c backward.c update.c log_loss.c matrix_product_t.c matrix_product.c
LIB_SRC = ../../Lib/strcomp.c ../../Lib/shuffle.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = poc

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
