# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g -lm
SRC = ../sigmoid.c ../sigmoid_prime.c poc_train.c forward.c backward.c update.c log_loss.c
LIB_SRC = ../../Lib/strcomp.c ../../Lib/shuffle.c ../../Lib/matrix_product_t.c ../../Lib/matrix_product.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = poc

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
