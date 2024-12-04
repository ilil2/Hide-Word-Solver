CC = gcc
CFLAGS = -Wall -O2 -fsanitize=address
LDFLAGS = -lSDL2 -lSDL2_image -lm -fsanitize=address

OBJ = main.o auto_rotation.o manual_rotation.o detection_angle.o display.o ../Preprocessing/binarization.o ../Preprocessing/grayscale.o ../Preprocessing/medianfilter.o ../Preprocessing/sort.o sobel.o

all: rotation

rotation: $(OBJ)
	$(CC) -o rotation $(OBJ) $(LDFLAGS)

main.o: main.c rotation.h
	$(CC) $(CFLAGS) -c main.c

auto_rotation.o: auto_rotation.c rotation.h
	$(CC) $(CFLAGS) -c auto_rotation.c

manual_rotation.o: manual_rotation.c rotation.h
	$(CC) $(CFLAGS) -c manual_rotation.c

detection_angle.o: detection_angle.c rotation.h
	$(CC) $(CFLAGS) -c detection_angle.c

display.o: display.c rotation.h
	$(CC) $(CFLAGS) -c display.c

../Preprocessing/binarization.o: ../Preprocessing/binarization.c ../Preprocessing/binarization.h
	$(CC) $(CFLAGS) -c ../Preprocessing/binarization.c -o ../Preprocessing/binarization.o

../Preprocessing/grayscale.o: ../Preprocessing/grayscale.c ../Preprocessing/grayscale.h
	$(CC) $(CFLAGS) -c ../Preprocessing/grayscale.c -o ../Preprocessing/grayscale.o

../Preprocessing/medianfilter.o: ../Preprocessing/medianfilter.c ../Preprocessing/medianfilter.h
	$(CC) $(CFLAGS) -c ../Preprocessing/medianfilter.c -o ../Preprocessing/medianfilter.o

../Preprocessing/sort.o: ../Preprocessing/sort.c ../Preprocessing/sort.h
	$(CC) $(CFLAGS) -c ../Preprocessing/sort.c -o ../Preprocessing/sort.o

sobel.o: sobel.c ../Preprocessing/sobel.h
	$(CC) $(CFLAGS) -c sobel.c

.PHONY: clean
clean:
	rm -f *.o rotation ../Preprocessing/*.o
