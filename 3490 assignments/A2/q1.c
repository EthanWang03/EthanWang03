/*
Ethan Wang
1184940
A2 cis 3490
feb 14th 2023
*/


#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//insertion sort
void insertionSort(int data[], int n){
    int sorted;
    int unsorted;
    int counter = 0;

    for(int i = 1; i < n; i++){

        //mark first element as sorted
        sorted = data[i];

        //unsorted hold the number of "unsorted" elements
        unsorted = i - 1;

        while (unsorted >= 0 && data[unsorted] > sorted) {

            //inversion
            data[unsorted + 1] = data[unsorted];
            counter = counter + 1;
            unsorted = unsorted - 1;
        }

        data[unsorted + 1] = sorted;
    }

    printf("Count = %d\n",counter);
}

int main(){
    char filename[100];
    FILE *file;
    printf("Enter filename: ");
    scanf(" %s", filename);
    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    int data[50000];

    double i;
    int index = 0;
    while(i != EOF){
        i = fscanf(file, "%d %d %d %d %d", &data[index], &data[index+1], &data[index+2], &data[index+3], &data[index+4]);
        index = index + 5;
    }

    int n = sizeof(data)/sizeof(data[0]);

    printf("=============\n");
    printf("A Brute force program for counting inversions\n");
    clock_t start = clock();
    insertionSort(data,n);
    clock_t stop = clock();
    printf("Execution time: %fs\n", (double)(stop - start)/CLOCKS_PER_SEC);
    printf("=============\n");
}