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


//sorts smaller arrays from mergesort 
int merge (int data[], int min, int mid, int max){
    int i;
    int index;
    int low;
    int temp[50000];
    int counter = 0;

    low = min;
    i = min;
    index = mid;

    //runs through entire array
    while((low < mid) && (index < max+1)){
        //sorts lower half
        if(data[low] <= data[index]){
            temp[i] = data[low];
            low = low + 1;
        }
        //sorts upper half
        else{
            temp[i] = data[index];
            index = index + 1;
            //adjust counter for amount sorted
            counter = counter + mid - low;
        }
        i = i + 1;
    }

    //copy sorted values into temp
    if(low > mid - 1){
        for(int k = index; k < max+1; k++){
            temp[i] = data[k];
            i = i + 1;
        }
    }
    else{
        for(int k = low; k < mid + 1; k++){
            temp[i] = data[k];
            i = i + 1;
        }
    }
    
    //save sorted values into data array
    for(int k = min; k < max + 1; k++){
        data[k] = temp[k];
    }

    return counter;
}

//breaks array into smaller arrays for merge
int mergeSort(int data[],int min, int max){
    int mid;
    int inversion = 0;

    if (min < max){
        //split array into 2 at middle
        mid = (min + max)/2;

        //break first half into half
        inversion = inversion + mergeSort(data,min,mid);
        //break second half into half
        inversion = inversion + mergeSort(data,mid+1,max);
        //sort array
        inversion = inversion + merge(data,min,mid+1,max);
    }

    return inversion;
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

    printf("A divide and conquer program for counting inversions\n");
    clock_t begin = clock();
    printf("Count = %d\n",mergeSort(data, 0, n-1));
    clock_t end = clock();
    printf("Execution time: %fs\n", (double)(end - begin)/CLOCKS_PER_SEC);

    printf("=============\n");

}