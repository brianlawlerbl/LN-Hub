CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)
all		:	httpserver

httpserver	:	httpserver.o bind.o methodGET.o 
		$(CC) $(CFLAGS) -o httpserver httpserver.o bind.o methodGET.o

httpserver.o	:	httpserver.c 
		$(CC) $(CFLAGS) -c httpserver.c

bind.o	: bind.c
		$(CC) $(CFLAGS) -c bind.c

methodGET.o	: methodGET.c
		$(CC) $(CFLAGS) -c methodGET.c

format	:
		clang-format -style=LLVM -i *.c *.h

clean		:
		rm -f httpserver *.o *.gch
