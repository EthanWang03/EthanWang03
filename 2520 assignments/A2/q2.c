#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Stack{
   int top;
   unsigned capacity;
   double* array;
};

//creates stack
struct Stack * createStack(unsigned capacity){
   struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
   stack -> capacity = capacity;
   stack -> top = -1;
   stack -> array = (double*)malloc(stack -> capacity * sizeof(double));
   return stack;
}
//checks if stack is full
double isFull(struct Stack* stack){
   return stack -> top == stack -> capacity - 1;
}
//checks if stack is empty
double isEmpty(struct Stack* stack){
   return stack -> top == -1;
}
//adds item to top of stack
void push(struct Stack* stack, double item){
   if(isFull(stack)){
      return;
   }
   stack -> array[++stack->top] = item;
}
//returns element at the top of the stack
double pop(struct Stack* stack){
   if(isEmpty(stack)){
      return 0;
   }
   return stack -> array[stack->top--];
}
int main( int argc, char *argv[] )  {
   if( argc == 2 ) { //checks for correct amount of command line arguments
      printf("The argument supplied is %s\n", argv[1]);
      int length = strlen(argv[1]);
      char *str = (char *)malloc(length*sizeof(char));
      strcpy(str, argv[1]);
      //copys command line input to string
      int *ints = (int *) malloc(sizeof(int));
      char *symbols = (char *)malloc(sizeof(char));
      //array which stores all the number values
      int numCounter = 0;
      int symbolCounter = 0;

      for(int i = 0; i < length; i++){
         if(isdigit(str[i])){ //if element in input is a number
            ints = (int *)realloc(ints,sizeof(char));
            char temp[1];
            temp[0] = str[i]; 
            //creates temp char variable in order to atoi
            ints[numCounter] = atoi(temp); 
            //populates ints with the number value
            numCounter = numCounter + 1;
         }
         else{
            symbolCounter = symbolCounter + 1;
            //counts the number of operations
         }
      }
      
      struct Stack* stack = createStack(numCounter);
      //creates stack

      double num1;
      double num2;
      int counter = 0;
      for(int i = 0; i < length; i++){
         switch(str[i]){ //switch for signs in input
            case '+':
               push(stack,pop(stack)+pop(stack));
               break;
            case '-':
               num1 = pop(stack); 
               num2 = pop(stack);
               push(stack,num2-num1);
               //uses num1 and num2 to subtract properly
               break;
            case '*':
               push(stack,pop(stack)*pop(stack));
               break;
            case '/':
               num1 = pop(stack);
               num2 = pop(stack);
               //uses num1 and num2 to divide properly
               if(num1 != 0){
                  push(stack,num2/num1);
               }
               //checks for 0 divisor
               else{
                  printf("error: zero divisor\n");
                  return 0;
               }
               break;
            default: 
            // if input element is not a symbol push the numbers into the stack
               push(stack,(double)ints[counter]);
               counter = counter + 1;
         }
      }
      printf("Answer is %.2f\n",pop(stack));
      printf("%d opperations executed",symbolCounter);
      //prints answer to two decimal
      free(stack);
      free(symbols);
      free(ints);
      free(str);
      return 0;
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
   return 0;
}