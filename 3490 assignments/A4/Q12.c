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
    float probability;
    struct node *left;
    struct node *right;
};

//new node creation
struct node* newNode(char key[MAX_WORD_LEN], float probability) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    strcpy(node->key, key);
    node->probability = probability;
    node->left = node->right = NULL;
    return node;
}

//create greedy bst
struct node* createBST(char words[][MAX_WORD_LEN], float probabilities[], int start, int end) {
    //if no words left in sequence
    if(start > end){
        return NULL;
    }

    //Find word with maximum probability and make it root
    int maxProbIndex = start;
    for(int i = start; i < end; i++){  
        if(probabilities[i] > probabilities[maxProbIndex]){
            maxProbIndex = i;
        }
    }
    //printf("%s: %.3f\n",words[maxProbIndex], probabilities[maxProbIndex]);
    struct node* root = newNode(words[maxProbIndex], probabilities[maxProbIndex]);

    //Recursively create left and right subtrees
    root->left = createBST(words, probabilities, start, maxProbIndex - 1);
    root->right = createBST(words, probabilities, maxProbIndex + 1, end);

    return root;
}

//search bst
void search_bst(struct node* root, const char* word) {
    if (root == NULL) {
        printf("not found\n");
        return;
    }

    int cmp = strcmp(root->key, word);
    if (cmp == 0) {
        printf("Comparing with %s (%.3f), found\n", root->key, root->probability);
        return;
    }
    //if root key is alphabetically greater than word go right
    else if (cmp < 0) {
        printf("Comparing with %s (%.3f), go right subtree\n", root->key, root->probability);
        search_bst(root->right, word);
    }
    //if root key is alphabetically lower than word go left
    else {
        printf("Comparing with %s (%.3f), go left subtree\n", root->key, root->probability);
        search_bst(root->left, word);
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

    float P[wordCount];
    for(int i = 0; i < wordCount + 1; i++){
        P[i] = (float)freq[i]/total;
    }
    //sort alphabetically
    for (int i = 1; i < wordCount; i++) {
        char temp[MAX_WORD_LEN];
        float Ptemp = P[i];
        strcpy(temp, words[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(words[j], temp) > 0) {
            strcpy(words[j + 1], words[j]);
            P[j+1] = P[j];
            j--;
        }
        strcpy(words[j + 1], temp); 
        P[j + 1] = Ptemp;
    }

    struct node* root = createBST(words,P,1,wordCount);

    printf("Enter a key: ");
    scanf(" %s", search);

    search_bst(root, search);

    //free all mallocs
    free(contents);
    freeTree(root);
    fclose(file);
    return 0;
}