ifdef NDEBUG
  ndebug=-DNDEBUG
else
  ndebug=
endif

homedir=../../..
incdir=${homedir}/include
libdir=${homedir}/lib

sources = set.h set.c setdemo.c makefile
derived = set.o

all: set.o setdemo

setdemo: setdemo.c set.o
	gcc ${ndebug} setdemo.c -o setdemo -I${incdir} -L${libdir} set.o -llinked_clists -lchained_hts

set.o: set.h set.c
	gcc -c ${ndebug} set.c -c -I${incdir} -L${libdir} -llinked_clists

clean:
	/bin/rm -f $(derived) *.o

