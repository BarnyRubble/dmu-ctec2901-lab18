ifdef NDEBUG
  ndebug=-DNDEBUG
else
  ndebug=
endif

sources = set.h set.c setdemo.c makefile
derived = set.o

all: set.o setdemo

setdemo: setdemo.c set.o
	gcc ${ndebug} setdemo.c -o setdemo -I${HOME}/include -L${HOME}/lib set.o -llinked_clists

set.o: set.h set.c
	gcc -c ${ndebug} set.c -c -I${HOME}/include -L${HOME}/lib -llinked_clists

clean:
	/bin/rm -f $(derived) *.o

