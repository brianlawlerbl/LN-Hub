CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)
all		:	httpserver

httpserver	:	httpserver.o bind.o methodGET.o responseline.o
		$(CC) $(CFLAGS) -o httpserver httpserver.o bind.o methodGET.o responseline.o

httpserver.o	:	httpserver.c 
		$(CC) $(CFLAGS) -c httpserver.c

bind.o	: bind.c
		$(CC) $(CFLAGS) -c bind.c

methodGET.o	: methodGET.c
		$(CC) $(CFLAGS) -c methodGET.c

responseline.o	: responseline.c
		$(CC) $(CFLAGS) -c responseline.c

format	:
		clang-format -style=LLVM -i *.c *.h

clean		:
		rm -f httpserver *.o *.gch *.out

me	:
		@echo ""

smile	:
		@echo "Hope you're having a good day :)"