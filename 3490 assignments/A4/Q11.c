/*
Ethan Wang
1184940
A4 cis 3490
March 27 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_WORDS 1000 // maximum number of words
#define MAX_WORD_LEN 50 // maximum length of each word

//tree struct
struct node {
    char key[MAX_WORD_LEN];
    float C;
    struct node *left;
    struct node *right;
};

//create new node
struct node* newNode(char key[MAX_WORD_LEN], float C) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    strcpy(node->key, key);
    node->C = C;
    node->left = node->right = NULL;
    return node;
}

//create Obst using root table
struct node* constructTree(char keys[][MAX_WORD_LEN], int **root, float ** C,int i, int j) {
    if (i > j) {
        return NULL;
    }
    int r = root[i][j];
    float d = C[i][j];

    struct node* node = newNode(keys[r-1],d);

    node->left = constructTree(keys, root, C, i, r-1);
    node->right = constructTree(keys, root, C, r+1, j);

    return node;
}

//search bst
void search_bst(struct node* root, const char* word) {
    if (root == NULL) {
        printf("not found\n");
        return;
    }

    int cmp = strcmp(root->key, word);
    if (cmp == 0) {
        printf("Comparing with %s (%.3f), found\n", root->key, root->C);
        return;
    }
    //if root key is alphabetically greater than word go right
    else if (cmp < 0) {
        printf("Comparing with %s (%.3f), go right subtree\n", root->key, root->C);
        search_bst(root->right, word);
    }
    //if root key is alphabetically lower than word go left
    else {
        printf("Comparing with %s (%.3f), go left subtree\n", root->key, root->C);
        search_bst(root->left, word);
    }
}

//populate C and R arrays using textbook pseudocode
void OptimalBST(float P[], int n, float **C, int **R){

    for(int i = 1; i <= n; i++){
        C[i][i-1] = 0;
        C[i][i] = P[i];
        R[i][i] = i;
    }
    C[n+1][n] = 0;

    float minval;
    int kmin;
    float sum;
    //dynamic programming
    for(int d = 1; d < n; d++){
        for(int i = 1; i <= n-d; i++){
            int j = i + d;
            minval = INT_MAX;
            for(int k = i; k <= j; k++) {
                if ((C[i][k-1] + C[k+1][j]) < minval) {
                    minval = C[i][k-1] + C[k+1][j];
                    kmin = k;   
                }
            }
            R[i][j] = kmin;
            sum = P[i];
            for(int s = i+1; s <= j; s++) {
                sum = sum + P[s];
            }
            C[i][j] = minval + sum;
        }
    }
}

//free tree
void freeTree(struct node* root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(){
    char filename[100] = "data_A4_Q1.txt";
    FILE *file;
    char *contents;
    int size;
    char *token;
    int wordCount = 0;
    int length;
    int total = 0;
    char search[100];

    char words[MAX_WORDS][MAX_WORD_LEN];    
    int freq[MAX_WORDS] = {0};

    //printf("Enter filename: ");
    //scanf(" %s", filename);

    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    contents = (char *) malloc(size + 1);

    if(contents == NULL) {
        printf("Error!");   
        return 0; 
    }

    fseek(file, 0, SEEK_SET);

    fread(contents, size, 1, file);

    token = strtok(contents," ");

    while(token != NULL){
        length = strlen(token);
        if(token[length-1] == '\n'){
            token[length-1] = '\0';
        }
        if(token[0] == '\n'){
            for(int j = 0; j < length + 1; j++){
                token[j-1] = token[j];
            }
            //token[i-1] = '\0';
        }
        if(strcmp("\0", token) != 0){
            int i;

            for (i = 0; i < wordCount; i++) {
                for(int j = 0; token[j]; j++){
                    token[j] = tolower(token[j]);
                }
                if (strcmp(words[i], token) == 0) {
                    freq[i] = freq[i] + 1;
                    total = total + 1;
                    break;
                }
            }
            if (i == wordCount) {
                if (wordCount == MAX_WORDS) {
                    fprintf(stderr, "Too many words!\n");
                    return 1;
                }
                for(int j = 0; token[j]; j++){
                    token[j] = tolower(token[j]);
                }
                strcpy(words[wordCount], token);
                freq[wordCount] = 1;
                wordCount = wordCount + 1;
                total = total + 1;
            }
        }
        token = strtok(NULL, " ");
    }

    float P[wordCount + 1];
    P[0] = 0;
    for(int i = 1; i < wordCount + 1; i++){
        P[i] = (float)freq[i-1]/total;
    }
    //sort alphabetically
    for (int i = 1; i < wordCount; i++) {
        char temp[MAX_WORD_LEN];
        float Ptemp = P[i+1];
        strcpy(temp, words[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(words[j], temp) > 0) {
            strcpy(words[j + 1], words[j]);
            P[j+2] = P[j+1];
            j--;
        }
        strcpy(words[j + 1], temp); 
        P[j+2] = Ptemp;
    }

    float **C = (float **)malloc((wordCount + 2) * sizeof(float *));
    for (int i = 0; i < wordCount + 2; i++) {
        C[i] = (float *)malloc((wordCount + 1) * sizeof(float));
    }

    // Allocate memory for R array
    int **R = (int **)malloc((wordCount + 1) * sizeof(int *));
    for (int i = 0; i < wordCount + 1; i++) {
        R[i] = (int *)malloc((wordCount + 1) * sizeof(int));
    }

    for(int i = 0; i < wordCount+2; i++){
        for(int j = 0; j < wordCount+1; j++){
            C[i][j] = 0;
        }
    }

    for(int i = 0; i < wordCount+1; i++){
        for(int j = 0; j < wordCount+1; j++){
            R[i][j] = 0;
        }
    }
    
    OptimalBST(P, wordCount, C, R);

    struct node* root = constructTree(words, R, C, 1, wordCount);

    printf("Enter a key: ");
    scanf(" %s", search);

    search_bst(root, search);

    //free all mallocs
    free(contents);
    freeTree(root);

    for(int i = 0; i < wordCount + 2; i++) {
        free(C[i]);
    }
    free(C);

    for(int i = 0; i < wordCount + 1; i++) {
        free(R[i]);
    }
    free(R);
    fclose(file);
    
    return 0;
}