CC=clang
CFLAGS=-Wall
FRAMEWORKS=-framework CoreFoundation -framework ApplicationServices -framework CoreGraphics

test: .build/build_artifacts application.o modal.o permissions.o utilities.o window.o window_manager.o
				$(CC) $(CFLAGS) $(FRAMEWORKS) test/test.c .build/build_artifacts/*.o -o .build/test

.build:
				mkdir .build

.build/build_artifacts: .build
				mkdir .build/build_artifacts

application.o:
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/application.c -o .build/build_artifacts/application.o

modal.o:
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/modal.c -o .build/build_artifacts/modal.o

permissions.o:
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/permissions.c -o .build/build_artifacts/permissions.o

utilities.o:
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/utilities.c -o .build/build_artifacts/utilities.o

window.o:
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/window.c -o .build/build_artifacts/window.o

window_manager.o:
				$(CC) $(CFLAGS) $(FRAMEWORKS) -c src/window_manager.c -o .build/build_artifacts/window_manager.o

clean:
				rm -r .build
