CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

all: basic-server

basic-server: basic-server.o
	$(CC) -o basic-server basic-server.o

basic-server.o: basic-server.c
	$(CC) -c basic-server.c

clean:
	rm *.o
