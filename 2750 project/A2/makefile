CC = clang
CFLAGS = -Wall -std=c99 -pedantic

all: libmol.so break molecule_wrap.o _molecule.so

libmol.so: mol.o
	$(CC) -shared -lm -o libmol.so mol.o

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c -fPIC mol.c -o mol.o

break: molecule.i
	swig -python molecule.i

molecule_wrap.o: molecule_wrap.c
#	$(CC) $(CFLAGS) -c molecule_wrap.c -fPIC -I /Program Files/Python311/include -o molecule_wrap.o
	$(CC) $(CFLAGS) -c molecule_wrap.c -fPIC -I /usr/include/python3.7m  -o molecule_wrap.o

_molecule.so: molecule_wrap.o
#	$(CC) -shared -lpython3.11 -lmol -dynamiclib -L. -L/Library/Frameworks/Python.framework/Versions/3.11/lib -o _molecule.so molecule_wrap.o
	$(CC) -shared -lpython3.7m -lmol -dynamiclib -L. -L/usr/lib/python3.7/config-3.7m-x86_64-linux-gnu -o _molecule.so molecule_wrap.o

clean: 
	rm -f libmol.so mol.o molecule_wrap.o _molecule.so