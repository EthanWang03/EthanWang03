CC = gcc
CFLAGS = -Wall -Werror -fPIC
LDFLAGS = -shared

SRC = mol.c test1.c
OBJ = mol.o test1.o
LIB = libmol.so

$(LIB): $(OBJ)
	$(CC) $(LDFLAGS) -lm -o $(LIB) $(OBJ)

mol.o: mol.c
	$(CC) $(CFLAGS) -c -o mol.o mol.c

test1.o: test1.c
	$(CC) $(CFLAGS) -c -o test1.o test1.c

clean:
	rm -f $(OBJ) $(LIB)
