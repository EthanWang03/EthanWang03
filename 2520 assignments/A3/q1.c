#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//binary tree
struct node {
    char data[5]; //variable symbol or number
    struct node* left;
    struct node* right;
    struct node* next;
};
struct node *head=NULL;

// push onto stack
int push(char stack[][2], int *top,int counter, char data[2]){
    if(*top == counter - 1){ // checks if stack is full
        return -1;
    }
    else{
        *top = *top + 1;
        strcpy(stack[*top], data);
        return 1;
    }
}

// pop element from stack
int pop(char stack[][2], int *top, char data[2]){
    if(*top == -1){ // checks if stack is empty
        return -1;
    }
    else{
        strcpy(data, stack[*top]);
        *top = *top - 1;
        return 1;
    }
}

//returns top element of stack
const char* peek(char stack[][2], int *top){
    return stack[*top];
}

//creates new node for tree
struct node* newNode(char data[5]){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    strcpy(node->data,data);
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    return (node);
}

//push new node onto tree
void pushNode(struct node* node){
    if(head == NULL){
        head = node;
    }
    else{
        node->next = head;
        head = node;
    }
}

//pop node and return data
struct node* popNode(){
    struct node* pop = head;
    head = head->next;
    return pop;
}

//recursive preorder traversal
void printPreorder(struct node* node)
{
    if (node == NULL){ // if tree is empty
        return;
    }
    else{
        if(isalpha(node->data[0])){ // for variable
            printf("%s[0.00] ", node->data);
        }
        else{
            printf("%s ", node->data);
        }
        printPreorder(node->left);
        printPreorder(node->right);
    }
}

//recursive postorder traversal
void printPostorder(struct node* node)
{
    if (node == NULL){
        return;
    }
    else{
        printPostorder(node->left);
        printPostorder(node->right);
        if(isalpha(node->data[0])){ // for variable
            printf("%s[0.00] ", node->data);
        }
        else{
            printf("%s ", node->data);
        }
    }
}

int main( int argc, char *argv[] )  {
    if( argc == 2 ) { //checks for correct amount of command line arguments
        int length;
        length = strlen(argv[1]);
        char *str = (char *)malloc(length*sizeof(char));
        char variable[3]; // used to store variable inputs
        int symbolCounter = 0;
        int counter = 0; // counter for the amount of elements in input
        char input; // for user input for menu

        strcpy(str, argv[1]);
        printf("\nThe argument supplied is %s\n", argv[1]);
        printf("\n");

        for(int i = 0; i < length; i++){
            if(str[i] == '(' || str[i] == ')'){
                symbolCounter = symbolCounter + 1;
                counter = counter + 1;
            }
            if(isalpha(str[i]) || str[i] == '.' || str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*'){
                counter = counter + 1;
            }
            //counts number of symbols
        }

        char infix[counter][5]; //array for infix input
        char postfix[counter - symbolCounter][5]; //array for postfix conversion
        int infixCounter = 0;
        int postfixCounter = 0;

        char stack[counter][2]; //creation of stack
        //length of 2 for symbol + \0
        char returned[2]; // returned data value

        int top;
        top = -1;   // Initialize Stack

        struct node *right; //declare nodes
        struct node *left;
        struct node *next;

        for(int i = 0; i < length; i++){
            //for loop user string input and store it in infix array
            if(str[i] == '(' || str[i] == ')'){
                //stores brakets
                infix[infixCounter][0] = str[i];
                infix[infixCounter][1] = '\0';
                infixCounter = infixCounter + 1;
            }
            else if(str[i] == '.'){
                //stores double values
                infix[infixCounter][0] = str[i-1];
                infix[infixCounter][1] = str[i];
                infix[infixCounter][2] = str[i+1];
                infix[infixCounter][3] = str[i+2];
                infix[infixCounter][4] = '\0';
                infixCounter = infixCounter + 1;
                i = i + 2;
            }
            else if(isalpha(str[i])){
                //stores variable
                variable[0] = str[i];
                variable[1] = str[i+1];
                variable[2] = '\0';
                i = i + 1;
                strcpy(infix[infixCounter],variable);
                infixCounter = infixCounter + 1;
            }
            else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*'){
                //stores symbols
                infix[infixCounter][0] = str[i];
                infix[infixCounter][1] = '\0';
                infixCounter = infixCounter + 1;
            }
        }
        
        for(int i = 0; i < counter; i++){
            //for loop converts infix array to postfix
            if(infix[i][1] == '.' || isalpha(infix[i][0])){
                //stores double values/variables
                strcpy(postfix[postfixCounter],infix[i]);
                postfixCounter = postfixCounter + 1;
                //printf("%s",infix[i]);
            }
            else if(infix[i][0] == '('){
                //pushes brakets into stack
                //checks if ( is going to be pushed ontop on symbol and rearanges stack
                if(peek(stack,&top)[0] == '+' || peek(stack,&top)[0] == '-' || peek(stack,&top)[0] == '*' || peek(stack,&top)[0] == '/'){
                    pop(stack,&top,returned);
                    push(stack,&top,counter,infix[i]);
                    push(stack,&top,counter,returned);
                }
                else{
                    push(stack,&top,counter,infix[i]);
                }
            }
            else if(infix[i][0] == ')'){
                // checks if elemnt is ) and pops symbols out of stack
                while(peek(stack,&top)[0] != '('){
                    //pops all symbols out of stack untill ( is reached
                    pop(stack,&top,returned);
                    strcpy(postfix[postfixCounter],returned);
                    postfixCounter = postfixCounter + 1;
                }
            }
            else{
                //pushes symbols into stack
                push(stack,&top,counter,infix[i]);
            }
        }

        //uses command line input converted to postfix to push into binary tree
        for (int i = 0; i < postfixCounter; i++) {
            if(postfix[i][0] == '+' ||postfix[i][0] == '-' || postfix[i][0] == '*' || postfix[i][0] == '/'){
                //creates new node for each symbol
                next = newNode(postfix[i]);
                right = popNode();
                left = popNode();
                //sets data
                next -> left = left;
                next -> right = right;
                //tree branches
                pushNode(next);
            }
            else{
                //pushes rest into tree
                next = newNode(postfix[i]);
                pushNode(next);
            }
        }
        while(1){
            //menu
            printf("Please select from the following options:\n");
            printf("1: Preorder\n");
            printf("2: Postorder\n");
            printf("3: Exit\n");
            scanf(" %c",&input);
            switch(input){
                case '1':
                    printf("Preorder Traversal of Tree: ");
                    printPreorder(next);
                    printf("\n");
                    printf("\n");
                    break;
                case '2':
                    printf("Postorder Traversal of Tree: ");
                    printPostorder(next);
                    printf("\n");
                    printf("\n");
                    break;
                case '3':
                    return 0;
                default: 
                    //invalid input
                    printf("Invalid input \n");
                    break;
            }
        }
    }
    //checks for invalid command line input
    else if( argc > 2 ) {
        printf("Too many arguments supplied.\n");
    }
    else {
        printf("One argument expected.\n");
    }
}