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

//find all subsets
void subset_sum(int a[], int d, int n, int sum, int* count, int* deadEnds) {
    if (sum == d) {
        (*count)++;
        return;
    }
    if (n == 0 || sum > d) {
        (*deadEnds)++;
        return;
    }
    subset_sum(a, d, n-1, sum, count, deadEnds);
    subset_sum(a, d, n-1, sum+a[n-1], count, deadEnds);
}

int cmpfunc (const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}


int main() {
    char input[100];
    char filename[50];
    FILE *file;
    char* token;
    int sum;
    clock_t t;
    int count = 0;
    int deadEnds = 0;

    printf("Backtracking program for subset sum problem\n");
    printf("Enter the file name and subset sum: ");
    fgets(input, sizeof(input), stdin);

    token = strtok(input, " ");
    strcpy(filename,token);

    token = strtok(NULL, " ");
    sum = atoi(token);

    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    int size = 0;
    int i;
    while (fscanf(file, "%d", &i) == 1) {
        size++;
    }

    int *array = (int *) malloc(size);
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }

    qsort(array, size, sizeof(int), cmpfunc); 
    t = clock();
    subset_sum(array, sum, size, 0, &count, &deadEnds);
    t = clock() - t;

    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("Number of dead ends: %d\n", deadEnds);
    printf("Number of subsets whose sums are %d: %d\n", sum, count);
    printf("Execution time: %fs\n", time_taken);
    return 0;
}
