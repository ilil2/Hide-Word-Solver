CC = gcc
CFLAGS = -lSDL2 -lSDL2_image -lm

AUTO_EXEC = rotation_auto
MANUAL_EXEC = rotation_manuel

AUTO_SRC = rotation_auto.c
MANUAL_SRC = rotation_manuel.c

all: $(AUTO_EXEC) $(MANUAL_EXEC)

$(AUTO_EXEC): $(AUTO_SRC)
	$(CC) -o $(AUTO_EXEC) $(AUTO_SRC) $(CFLAGS)

$(MANUAL_EXEC): $(MANUAL_SRC)
	$(CC) -o $(MANUAL_EXEC) $(MANUAL_SRC) $(CFLAGS)

clean:
	rm -f $(AUTO_EXEC) $(MANUAL_EXEC)
