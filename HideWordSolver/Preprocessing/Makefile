CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address
LDLIBS = -lm -lSDL2 -lSDL2_image
TARGET = main
OBJS = main.o grayscale.o binarization.o sobel.o medianfilter.o sort.o

${TARGET} : ${OBJS}
	$(CC) $(OBJS) $(CFLAGS) $(LDLIBS) -o $(TARGET)

.PHONY: clean
clean :
	${RM} ${TARGET} ${OBJS} *.png

.PHONY: img_clean
img_clean :
	${RM} *.png
