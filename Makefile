CC = clang

WINDOWS_CC = x86_64-w64-mingw32-gcc
WINDOWS_CFLAGS =  -I./include/ -ggdb -Wall -Werror `PKG_CONFIG_PATH=/usr/x86_64-w64-mingw32/sys-root/mingw/lib/pkgconfig/ pkg-config --cflags --libs gtk4`
WINDOWS_BUILD_DIR = ./build/win/

CLIBS = -lm
CFLAGS = `pkg-config --cflags gtk4` -I./include/ -ggdb -Wall -Werror `pkg-config --libs gtk4`
BUILD_DIR = ./build/

SRC = src/main.c src/cJSON.c src/stats.c

all: $(SRC)
	$(clean)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)main $(SRC) $(CLIBS)
	$(BUILD_DIR)main

windows: $(SRC)
	$(clean)
	$(WINDOWS_CC)  -o $(WINDOWS_BUILD_DIR)main.exe $(SRC) $(WINDOWS_CFLAGS) $(CLIBS)

parser:parser.py
	poetry shell && python parser.py

clean:
	rm -rf build/*

