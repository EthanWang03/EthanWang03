CC = gcc
CFLAGS = -Wall -std=c99 -lm

P11_OBJECTS = P11.o
P12_OBJECTS = P12.o
P21_OBJECTS = P21.o
P22_OBJECTS = P22.o
P23_OBJECTS = P23.o

all: P11 P12 P21 P22 P23

P11: $(P11_OBJECTS)
	$(CC) $(CFLAGS) $(P11_OBJECTS) -o P11

P12: $(P12_OBJECTS)
	$(CC) $(CFLAGS) $(P12_OBJECTS) -o P12

P21: $(P21_OBJECTS)
	$(CC) $(CFLAGS) $(P21_OBJECTS) -o P21

P22: $(P22_OBJECTS)
	$(CC) $(CFLAGS) $(P22_OBJECTS) -o P22

P23: $(P23_OBJECTS)
	$(CC) $(CFLAGS) $(P23_OBJECTS) -o P23

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o P11 P12 P21 P22 P23
