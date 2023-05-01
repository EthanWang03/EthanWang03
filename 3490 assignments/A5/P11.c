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
int subsetSumBruteForce(int set[], int n, int targetSum) {
    int count = 0;
    int i, j;

    //find the number of subsets (2^N) using bit manipulation
    for (i = 0; i < (1 << n); i++) {
        int subsetSum = 0;
        for (j = 0; j < n; j++) {
            //use bit manipulation to check if jth bit of i is 1 or 0
            if (i & (1 << j)) {
                subsetSum += set[j];
            }
        }
        if (subsetSum == targetSum) {
            count++;
        }
    }
    return count;
}

int main() {
    char input[100];
    char filename[50];
    FILE *file;
    char* token;
    int sum;
    clock_t t;

    printf("Brute force program for subset sum problem\n");
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

    //get number of numbers in file
    while (fscanf(file, "%d", &i) == 1) {
        size++;
    }

    int *array = (int *) malloc(size);
    fseek(file, 0, SEEK_SET);

    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &array[i]);
    }
    t = clock();
    int count = subsetSumBruteForce(array, size, sum);
    t = clock() - t;

    int totalSubsets = (1 << size);

    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("Number of all the subsets: %d\n", totalSubsets);
    printf("Number of subsets whose sums are %d: %d\n", sum, count);
    printf("Execution time: %fs\n", time_taken);
    
    return 0;
}
