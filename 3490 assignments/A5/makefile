CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lm

all: P11 P12 P21

P11: P11.c
	$(CC) $(CFLAGS) P11.c -o P11 $(LIBS)

P12: P12.c
	$(CC) $(CFLAGS) P12.c -o P12 $(LIBS)

P21: P21.c
	$(CC) $(CFLAGS) P21.c -o P21 $(LIBS)

clean:
	rm -f P11 P12 P21