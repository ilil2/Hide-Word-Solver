CC = gcc

CFLAGS = -lSDL2 -lSDL2_image -lm

OBJ = main.o auto_rotation.o manual_rotation.o display.o

all: rotation

rotation: $(OBJ)
	$(CC) -o rotation $(OBJ) $(CFLAGS)

main.o: main.c rotation.h
	$(CC) -c main.c $(CFLAGS)

auto_rotation.o: auto_rotation.c rotation.h
	$(CC) -c auto_rotation.c $(CFLAGS)

manual_rotation.o: manual_rotation.c rotation.h
	$(CC) -c manual_rotation.c $(CFLAGS)

display.o: display.c rotation.h
	$(CC) -c display.c $(CFLAGS)

clean:
	rm -f $(OBJ) rotation
