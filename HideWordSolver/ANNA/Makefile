# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g -lm -pthread -O3
SRC = neural_network.c reset_parameter.c save_parameter.c load_parameter.c load_image.c sigmoid.c sigmoid_prime.c train.c forward.c backward.c update.c log_loss.c convert_char_to_output.c convert_output_to_char.c save_stats.c relu.c relu_prime.c activ.c activ_prime.c softmax.c save_hyperparameter.c load_hyperprameter.c reset_hyperparameter.c reset_anna.c reset_all.c init_param.c init_adam.c load_layer.c
LIB_SRC = ../Lib/matrix_product.c ../Lib/matrix_product_t.c ../Lib/matrix_addition.c ../Lib/matrix_transpose.c ../Lib/strcomp.c ../Lib/shuffle.c ../Lib/matrix_shuffle.c ../Lib/atoi.c ../Lib/max.c ../Lib/create_file.c
OBJ = $(SRC:.c=.o) $(LIB_SRC:.c=.o)
EXE = ANNA

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(EXE)
