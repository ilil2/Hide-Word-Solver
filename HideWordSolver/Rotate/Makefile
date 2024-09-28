CC = gcc
CFLAGS = -lSDL2 -lSDL2_image -lm

EXEC = rotation
SRC_MAIN = main.c
SRC_AUTO = auto_rotation.c
SRC_MANUAL = manual_rotation.c
SRC_DISPLAY = display.c 


all: $(EXEC)

$(EXEC): $(SRC_MAIN) $(SRC_AUTO) $(SRC_MANUAL) $(SRC_DISPLAY)
	$(CC) -o $(EXEC) $(SRC_MAIN) $(SRC_AUTO) $(SRC_MANUAL) $(SRC_DISPLAY) $(CFLAGS)


clean:
	rm -f $(EXEC)
