#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct tree {
    int sumKey;
    int switched;
    int key[3];
    int content[7];
    struct tree* left;
    struct tree* right;
} Tree;

void readFile(int array [20][10]){
    FILE* file;
    file = fopen("f.dat", "r");
    if(file == NULL){
        printf("Error opening file!\n");
    }
    else{
        for(int row = 0; row < 20; row++){
            fscanf(file,"%d %d %d %d %d %d %d %d %d %d", &array[row][0], &array[row][1], &array[row][2], &array[row][3], &array[row][4], &array[row][5], &array[row][6], &array[row][7], &array[row][8], &array[row][9]);
        }
    }
}

void printArray(int array [20][10]){
    for(int row = 0; row < 20; row++){
        printf("%-3d  | ", array[row][0] + array[row][1] + array[row][2]);
        for(int col = 3; col < 10; col++){
            if(array[row][col] < 10){
                printf("0%d ", array[row][col]);
            }
            else{
                printf("%d ", array[row][col]);
            }
        }
        printf("\n");
    }
}

void createTree (Tree **tree, int size, int index, int data[20][10]){
    if (index < size){
        *tree = malloc(sizeof(**tree));
        int content[7] = {data[index][3], data[index][4], data[index][5], data[index][6], data[index][7], data[index][8], data[index][9]};
        
        (*tree)->sumKey = (data[index][0] + data[index][1] + data[index][2]);
        //printf("%d ",(*tree)->sumKey);

        for(int i = 0; i < 3; i++){
            (*tree)->key[i] = data[index][i]; 
        }
        for(int i = 0; i < 7; i++){
            (*tree)->content[i] = content[i]; 
        }
        (*tree)->switched = 0;
        (*tree)->left = NULL;
        (*tree)->right = NULL;

        createTree(&(*tree)->left, size, 2 * index + 1, data); //insert left
        createTree(&(*tree)->right, size, 2 * index + 2, data); //insert right
    }
}

void printLeft(Tree *tree){
    printf("%d ", tree->left->sumKey);
}

void printRight(Tree *tree){
    printf("%d ", tree->right->sumKey);
}

void printArrayOrder(Tree *tree)
{
    if (tree == NULL)
        return;
 
    printf("%d ", tree->sumKey);

    printLeft(tree);
    printRight(tree);

    printLeft(tree->left);
    printRight(tree->left);

    printLeft(tree->right);
    printRight(tree->right);

    printLeft(tree->left->left);
    printRight(tree->left->left);

    printLeft(tree->left->right);
    printRight(tree->left->right);

    printLeft(tree->right->left);
    printRight(tree->right->left);

    printLeft(tree->right->right);
    printRight(tree->right->right);

    printLeft(tree->left->left->left);
    printRight(tree->left->left->left);

    printLeft(tree->left->left->right);
    printRight(tree->left->left->right);

    printLeft(tree->left->right->left);
    printf("\n");
}

void swap(Tree *address, Tree *root){
    Tree *temp = malloc(sizeof(Tree));
    temp->sumKey = address->sumKey;
    //temp->sumKey = 300;
    for(int i = 0; i < 3; i++){
        temp->key[i] = address->key[i]; 
    }
    for(int i = 0; i < 7; i++){
        temp->content[i] = address->content[i]; 
    }

    address->sumKey = root->sumKey;
    //address->sumKey = 300;
    address->switched = 1;
    for(int i = 0; i < 3; i++){
        address->key[i] = root->key[i]; 
    }
    for(int i = 0; i < 7; i++){
        address->content[i] = root->content[i]; 
    }

    root->sumKey = temp->sumKey;
    root->switched = 1;
    for(int i = 0; i < 3; i++){
        root->key[i] = temp->key[i]; 
    }
    for(int i = 0; i < 7; i++){
        root->content[i] = temp->content[i]; 
    }
}

void search(Tree* root, int min, Tree *address) {
    int smallest = min;
    if(root != NULL) {
        if(root->sumKey < min){
            printf("%d ",address->sumKey);
            swap(address,root);
            smallest = address->sumKey;
        }   
        search(root->left, smallest, address);       
        search(root->right, smallest, address);
    }
}

void print(Tree *t, int level){
    if (t) {
        print(t->left, level + 1);
        printf("%*s->%d\n", 4*level, "", t->sumKey);
        print(t->right, level + 1);
    }
}

int main(){
    int array[20][10];
    int size = 20;
    Tree *tree;

    readFile(array);
    printArray(array);
    createTree(&tree,size,0,array);
    //printArrayOrder(tree);
    //Tree *address = tree;
    //search(tree, 80, address);
    //print(tree,0);
    /*
                                    79 <- you are here
                      ______________|_____________
                     /                            \
                   117                            143
             _______|______                 _______|______
            /              \               /              \
           83              64             223             118
          / \             / \             / \             / \
         /   \           /   \           /   \           /   \
        /     \         /     \         /     \         /     \
      144     146     130     156     115     132     138     150 
      / \     / \     /
     96 212 203 176 129
    */
    /*
                                    64
                      ______________|_____________
                     /                            \
                    79                            115
             _______|______                 _______|______
            /              \               /              \
           83             117             132             118
          / \             / \             / \             / \
         /   \           /   \           /   \           /   \
        /     \         /     \         /     \         /     \
       96     146     129     156     223     143     138     150
      / \     / \     /
    144 212 203 176 130
    */
}//4 5 6 7 8 14 
/*
                                    79
                      ______________|_____________
                     /                            \
                    83                            143
             _______|______                 _______|______
            /              \               /              \
          117              83             118             138
          / \             / \             / \             / \
         /   \           /   \           /   \           /   \
        /     \         /     \         /     \         /     \
      117     146     129     156     223     132     143     150
      / \     / \     /
    144 212 203 176 130
    */