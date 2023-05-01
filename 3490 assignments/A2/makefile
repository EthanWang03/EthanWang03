all: q1 q12 q2 q22

q1: q1.o
	gcc -Wall -std=c99 q1.o -o q1

q1.o: q1.c
	gcc -Wall -std=c99 -c q1.c

q12: q12.o
	gcc -Wall -std=c99 q12.o -o q12

q12.o: q12.c
	gcc -Wall -std=c99 -c q12.c

q2: q2.o
	gcc -Wall -std=c99 q2.o -o q2

q2.o: q2.c
	gcc -Wall -std=c99 -c q2.c

q22: q22.o
	gcc -Wall -std=c99 q22.o -o q22

q22.o: q22.c
	gcc -Wall -std=c99 -c q22.c

clean:
	rm *.o q1 q2 q2 q22