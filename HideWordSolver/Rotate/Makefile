CC = gcc
CFLAGS = -lSDL2 -lSDL2_image -lm

OBJ = main.o auto_rotation.o manual_rotation.o rotation_detection.o display.o ../Preprocessing/binarization.o ../Preprocessing/grayscale.o sobel.o

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

../Preprocessing/binarization.o: ../Preprocessing/binarization.c ../Preprocessing/preprocessing.h
	$(CC) -c ../Preprocessing/binarization.c -o ../Preprocessing/binarization.o

../Preprocessing/grayscale.o: ../Preprocessing/grayscale.c ../Preprocessing/preprocessing.h
	$(CC) -c ../Preprocessing/grayscale.c -o ../Preprocessing/grayscale.o

sobel.o: sobel.c ../Preprocessing/preprocessing.h
	$(CC) -c sobel.c

clean:
	rm -f *.o rotation ../Preprocessing/*.o
