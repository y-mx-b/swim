CC=clang
CFLAGS=-W -Wall -O2
FRAMEWORKS=-framework CoreFoundation -framework ApplicationServices -framework CoreGraphics

SRC=$(wildcard src/*.c)
OBJ=$(SRC:src/%.c=.build/build_artifacts/%.o)

TEST_SRC=$(wildcard test/*.c)
TEST_EXEC=$(TEST_SRC:test/%.c=.build/tests/%)


### TESTS
tests: .build/tests $(TEST_EXEC)

.build/tests/%: lib/libswim.a $(OBJ) test/%.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) $^ -o $@


### LIBS
# library
lib/libswim.a: lib .build/build_artifacts $(OBJ)
				ar rcs $@ .build/build_artifacts/*.o


### OBJ
.build/build_artifacts/%.o: src/%.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c $^ -o $@


### FILE SETUP
.build:
				mkdir .build

.build/build_artifacts: .build
				mkdir .build/build_artifacts

.build/tests: .build
				mkdir .build/tests
lib:
				mkdir lib


### MISC
FORCE: ;
docs: FORCE
				doxygen
clean:
				rm -r .build lib
