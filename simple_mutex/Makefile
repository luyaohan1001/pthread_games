CC=g++
CFLAGS=-Wall
LDFLAGS=-lncurses -lpthread

target:
	$(CC) main.cpp -o main $(CFLAGS) $(LDFLAGS)

.PHONY: clean run format

run: target
	./main

clean:
	rm -rf main

format:
	clang-format -i main.cpp