Ethan Wang, 1184940, A2 for cis 2520 

q1.c
compile using terminal command
gcc -Wall -std=c99 q1.c -o q1

execute using terminal command
./q1

proper output example:
=============MENU=============
1: Add new car to Available to rent list
2: Return a rented car to Available to rent list
3: Return a rented car to the Repair list
4: Transfer a car from Repair list to Available list
5: Rent the first available car
6: Print all the lists
7: Quit
==============================

Choose a menu option:

program works for invalid inputs such as characters/strings and numbers greater than 7 and less than 1
program checks linked list to see if licence plate is already in use before adding a new one
does not check for plate validity when loading file

q2.c
compile using terminal command
gcc -Wall -std=c99 q2.c -o q2

execute using terminal command
./q2 (command line argument here)

proper output example:
./q2 12+53-*12+53-*+
The argument supplied is 12+53-*12+53-*+
Answer is 12.00

./q2 12+53-*12+53-*+
The argument supplied is 12+53-*
Answer is 6.00

program works for correct notation
program checks for incorrect command line argument
program does not check for invalid notation