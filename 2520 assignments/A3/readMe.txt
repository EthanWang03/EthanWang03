Ethan Wang, 1184940, A3 for cis 2520 

q1.c
compile using terminal command
gcc -Wall -std=c99 q1.c -o q1

execute using terminal command
./q1 'command line argument goes here'

proper output example:
./q1 '(2.00*(x1-1.00))+(x2/3.00))'

The argument supplied is (2.00*(x1-1.00))+(x2/3.00))

Please select from the following options:
1: Preorder
2: Postorder
3: Exit
1
Preorder Traversal of Tree: + * 2.00 - x1[0.00] 1.00 / x2[0.00] 3.00 

Please select from the following options:
1: Preorder
2: Postorder
3: Exit
2
Postorder Traversal of Tree: 2.00 x1[0.00] 1.00 - * x2[0.00] 3.00 / + 

Please select from the following options:
1: Preorder
2: Postorder
3: Exit
3

program checks for invalid menu command such as wrong numbers or letters
program does not check for invalid format of command line 
program only works for variable 2 chars long and starting with a char ie x3
program numbers must be double and must have 2 decimal places
