CC=clang
CFLAGS=-W -Wall -O2
FRAMEWORKS=-framework CoreFoundation -framework ApplicationServices -framework CoreGraphics

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=build/build_artifacts/%.o)

# tests
window_information: libswim.a $(OBJ) build/tests
				$(CC) $(CFLAGS) $(FRAMEWORKS) test/window_information.c lib/* -o build/tests/window_information

# library
libswim.a: lib build/build_artifacts $(OBJ)
				ar rcs lib/$@ build/build_artifacts/*.o

lib:
				mkdir lib

# build directory
build:
				mkdir build

build/build_artifacts: build
				mkdir build/build_artifacts

build/tests: build
				mkdir build/tests

# source files
build/build_artifacts/%.o: src/%.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c $^ -o $@

clean:
				rm -r build lib
