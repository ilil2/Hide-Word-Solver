CC = gcc
CFLAGS = -lSDL2 -lSDL2_image -lm

OBJ = main.o auto_rotation.o manual_rotation.o rotation_detection.o display.o binarization.o grayscale.o sobel.o

all: rotation

rotation: $(OBJ)
	$(CC) -o rotation $(OBJ) $(CFLAGS)

main.o: main.c rotation.h
	$(CC) -c main.c

auto_rotation.o: auto_rotation.c rotation.h
	$(CC) -c auto_rotation.c

manual_rotation.o: manual_rotation.c rotation.h
	$(CC) -c manual_rotation.c

rotation_detection.o: rotation_detection.c rotation.h
	$(CC) -c rotation_detection.c

display.o: display.c rotation.h
	$(CC) -c display.c

binarization.o: binarization.c preprocessing.h
	$(CC) -c binarization.c

grayscale.o: grayscale.c preprocessing.h
	$(CC) -c grayscale.c

sobel.o: sobel.c preprocessing.h
	$(CC) -c sobel.c

clean:
	rm -f *.o rotation
