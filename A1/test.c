#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int count = 0;


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

// swap values
void swap(int *a, int *b, int *counter){
    int swapped = *a;
    *a = *b;
    *b = swapped;
}

int partition(int data[], int low, int high, int *counter){
    //set rightmost point as pivot
    int pivot = data[high];

    //i holds the index of the element to swap
    int i = (low - 1);

    //compare each value to the pivot point
    for(int j = low; j < high; j++){
        if(data[j] <= pivot){
            //if smaller element is found swap with greater element
            i = i + 1;
            counter = counter + 1;
            swap(&data[i], &data[j], counter);
        }
    }

    //swap pivot point with greater element
    swap(&data[i + 1], &data[high], counter);

    //return partition point
    return (i+1);
}
void quickSort(int data[], int low, int high, int *counter){
    //if array has been split fully end recursion
    if(low < high){

        //puts elements greater than pivot to the right
        //puts elements smaller than pivot to the left
        int point = partition(data, low, high, counter);

        //left of pivot
        quickSort(data, low, point - 1, counter);

        //right of pivot
        quickSort(data, point + 1, high, counter);
    }
}


int merge (int data[], int min, int mid, int max){
    int i;
    int index;
    int k;
    int low;
    int temp[50000];
    int counter = 0;

    low = min;
    i = min;
    index = mid;

    while((low < mid) && (index < max+1)){
        if(data[low] <= data[index]){
            temp[i] = data[low];
            low = low + 1;
        }
        else{
            temp[i] = data[index];
            index = index + 1;
            counter = counter + mid - low;
        }
        i = i + 1;
    }

    if(low > mid - 1){
        for(k = index; k < max+1; k++){
            temp[i] = data[k];
            i = i + 1;
        }
    }
    else{
        for(k = low; k < mid + 1; k++){
            temp[i] = data[k];
            i = i + 1;
        }
    }
    
    for(k = min; k < max + 1; k++){
        data[k] = temp[k];
    }

    return counter;
}

int mergesort(int array[],int min, int max){
    int middle;
    int inversion = 0;

    if (min < max){
        middle = (min + max)/2;
        inversion = mergesort(array,min,middle);
        inversion = inversion + mergesort(array,middle+1,max);
        inversion = inversion + merge(array,min,middle+1,max);
    }

    return inversion;
}

int main()
{
    //char filename[100];
    FILE *file;
    //printf("Enter filename: ");
    //scanf(" %s", filename);
    file = fopen("data_A2_Q1.txt","r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    int data[50000];
    int data2[50000];

    double i;
    int index = 0;
    while(i != EOF){
        i = fscanf(file, "%d %d %d %d %d", &data[index], &data[index+1], &data[index+2], &data[index+3], &data[index+4]);
        index = index + 5;
    }

    int n = sizeof(data)/sizeof(data[0]);
    
    //clone data for quicksort
    for(int i = 0; i < n; i++){
        data2[i] = data[i];
    }

    printf("=============\n");
    printf("A Brute force program for counting inversions\n");
    clock_t start = clock();
    insertionSort(data,n);
    clock_t stop = clock();
    printf("Execution time: %fs\n", (double)(stop - start)/CLOCKS_PER_SEC);
    printf("=============\n");


    printf("A divide and conquer program for counting inversions\n");
    clock_t begin = clock();
    printf("Count = %d\n",mergesort(data2, 0, n-1));
    clock_t end = clock();
    printf("Execution time: %fs\n", (double)(end - begin)/CLOCKS_PER_SEC);

    printf("=============\n");
}