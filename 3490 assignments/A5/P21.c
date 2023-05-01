/*
Ethan Wang
1184940
A5 cis 3490
April 10 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//find the max val to maximize the assignments
void assign(int** V, int* perm, int n, int* max_perm, int* max_val) {
    int val = 0;
    for (int i = 0; i < n; i++) {
        val += V[i][perm[i]];
    }
    if (val > *max_val) {
        *max_val = val;
        for (int i = 0; i < n; i++) {
            max_perm[i] = perm[i];
        }
    }
}

//Heaps algo to find all permutations
void heap_perm(int** V, int* perm, int n, int* max_perm, int* max_val, int i) {
    if (i == 1) {
        assign(V, perm, n, max_perm, max_val);
        count++;
    } else {
        for (int j = 0; j < i - 1; j++) {
            heap_perm(V, perm, n, max_perm, max_val, i-1);
            if (i % 2 == 0) {
                swap(&perm[j], &perm[i-1]);
            } else {
                swap(&perm[0], &perm[i-1]);
            }
        }
        heap_perm(V, perm, n, max_perm, max_val, i-1);
    }
}

int main() {
    char filename[100];
    FILE *file;
    int size = 12;
    clock_t t;

    printf("Brute force program for assignment problem\n");
    printf("Enter the file name: ");
    scanf(" %s", filename);

    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    int** V = (int**) malloc(size * sizeof(int*));
    int* perm = (int*) malloc(size * sizeof(int));
    int* max_perm = (int*) malloc(size * sizeof(int));
    int max_val = -1;

    //read file
    for (int i = 0; i < size; i++) {
        V[i] = (int*) malloc(size * sizeof(int));
        for(int j = 0; j < size; j++){
            fscanf(file, "%d", &V[i][j]);
        }
    }

    for (int i = 0; i < size; i++) {
        perm[i] = i;
    }

    t = clock();
    heap_perm(V, perm, size, max_perm, &max_val, size);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("The number of all the possible assignments: %d\n", count);

    //reformat assignment to be relative to job
    printf("Assignment: ");
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            if(i == max_perm[j]){
                printf("%d ", j+1);
            }
        }
    }
    printf("\n");
    printf("Maximum value: %d\n", max_val);
    printf("Execution time: %fs\n", time_taken);

    for (int i = 0; i < size; i++) {
        free(V[i]);
    }
    free(V);
    free(perm);
    free(max_perm);

    return 0;
}