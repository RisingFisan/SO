CC = gcc
CFLAGS = -O2 -Wall
HEADERS = pessoas.h
DEPS = main.o

.PHONY: all clean
all: pessoas

pessoas: $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f pessoas *.o