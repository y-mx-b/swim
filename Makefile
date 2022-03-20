CC=clang
CFLAGS=-Wall
FRAMEWORKS=-framework CoreFoundation -framework ApplicationServices -framework CoreGraphics

test: .build/build_artifacts libswim.a
				$(CC) $(CFLAGS) $(FRAMEWORKS) test/test.c lib/* -o .build/test

libswim.a: lib .build/build_artifacts application.o modal.o permissions.o utilities.o window.o window_manager.o
				ar rcs lib/$@ .build/build_artifacts/*.o

lib:
				mkdir lib

.build:
				mkdir .build

.build/build_artifacts: .build
				mkdir .build/build_artifacts

application.o: src/application.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/application.c -o .build/build_artifacts/application.o

modal.o: src/modal.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/modal.c -o .build/build_artifacts/modal.o

permissions.o: src/permissions.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/permissions.c -o .build/build_artifacts/permissions.o

utilities.o: src/utilities.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/utilities.c -o .build/build_artifacts/utilities.o

window.o: src/window.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/window.c -o .build/build_artifacts/window.o

window_manager.o: src/window_manager.c
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/window_manager.c -o .build/build_artifacts/window_manager.o

clean:
				rm -r .build lib
