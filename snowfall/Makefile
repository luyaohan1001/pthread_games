CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-lncurses -lpthread

target:
	$(CC) main.c -o main $(CFLAGS) $(LDFLAGS)

.PHONY: clean run format

run: target
	./main

clean:
	rm -rf main

format:
	clang-format -i main.c