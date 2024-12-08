CC = gcc
CFLAGS = -Wall -Wextra -g
LDLIBS = -lm -lSDL2 -lSDL2_image #-fsanitize=address
TARGET = main
OBJS = main.o grayscale.o binarization.o sobel.o medianfilter.o sort.o

${TARGET} : ${OBJS}

extraction :
	gcc -Wall -Wextra -g -c -o extraction.o extraction.c
	gcc extraction.o -lm -lSDL2 -lSDL2_image -o extraction

.PHONY: clean
clean :
	${RM} ${TARGET} ${OBJS} *.png extracted_letters/*.png extraction extraction.o

.PHONY: img_clean
img_clean :
	${RM} *.png extracted_letters/*.png
