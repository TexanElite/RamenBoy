CC=gcc
LDFLAGS= -lSDL2

all: clean sdl

sdl:
	$(CC) *.c -o RamenBoy_SDL $(LDFLAGS)

clean:
	rm -rf RamenBoy_SDL