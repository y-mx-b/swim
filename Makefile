CC=clang
CFLAGS=-W -Wall -O2
FRAMEWORKS=-framework CoreFoundation -framework ApplicationServices -framework CoreGraphics

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=.build/build_artifacts/%.o)

# tests
window_information: libswim.a $(OBJ) .build/tests
				$(CC) $(CFLAGS) $(FRAMEWORKS) test/window_information.c lib/* -o .build/tests/window_information

set_window_frame: libswim.a $(OBC) .build/tests
				$(CC) $(CFLAGS) $(FRAMEWORKS) test/set_window_frame.c lib/* -o .build/tests/set_window_frame

# library
libswim.a: lib .build/build_artifacts $(OBJ)
				ar rcs lib/$@ .build/build_artifacts/*.o

lib:
				mkdir lib

# build directory
.build:
				mkdir .build

.build/build_artifacts: .build
				mkdir .build/build_artifacts

.build/tests: .build
				mkdir .build/tests

# source files
.build/build_artifacts/%.o: src/%.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c $^ -o $@

# build tests
# .build/tests/%: libswim.a $(OBJ) .build/tests test/%.c
# 				$(CC) $(CFLAGS) $(FRAMEWORKS) lib/* $^ -o $@

clean:
				rm -r .build lib
