CC = gcc
CLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -I./include/ -ggdb -Wall -Werror
BUILD_DIR = ./build/

SRC = src/main.c

all: $(SRC)
	$(clean)
	$(CC) $(CFLAGS) -o build/main $(SRC) $(CLIBS)
	$(BUILD_DIR)main

clean:
	rm -rf build/*

