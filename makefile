CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

all: basic-server

basic-server: basic-server.o
	$(CC) -o basic-server.exe basic-server.o

basic-server.o: basic-server.c
	$(CC) -c basic-server.c

clean:
	rm *.o *.exe

smiles:
	@echo "I love you"
