CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)
all		:	httpserver

httpserver	:	httpserver.o bind.o
		$(CC) $(CFLAGS) -o httpserver httpserver.o bind.o

httpserver.o	:	httpserver.c 
		$(CC) $(CFLAGS) -c httpserver.c

bind.o	: bind.c
		$(CC) $(CFLAGS) -c bind.c

clean		:
		rm -f httpserver *.o
