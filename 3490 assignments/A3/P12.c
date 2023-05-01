/*
Ethan Wang
1184940
A3 cis 3490
March 10 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//compare for qsort
int cmp(const void *a, const void *b) {
    int int_a = *((int*) a);
    int int_b = *((int*) b);
    if(int_a > int_b){
        return 1;
    }
    else if(int_a < int_b){
        return -1;
    }
    else{
        return 0;
    }
}


int max_common_intervals(int start[], int end[], int n) {
    
    // Sort the intervals
    qsort(start, n, sizeof(int), cmp);
    qsort(end, n, sizeof(int), cmp);

    int maxCounter = 0;
    int count = 0;
    int time = start[0];
    int i = 1;
    int j = 0;

    //search through intervals
    while(i < n && j < n){
        //if start before end
        if(start[i] < end[j]){
            count++;
            i++;
            if(count > maxCounter){
                maxCounter = count;
                time = start[i];
            }
        }
        //else start is after end
        else{
            count--;
            j++;
        }
    }

    printf("The intverals include point: %d\n",time);
    return maxCounter;
}


int main(){
    char filename[100];
    FILE *file;
    printf("Enter filename: ");
    scanf(" %s", filename);

    int start[30000];
    int end[30000];

    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");  
        return 0;             
    }

    //read file
    int i;
    int index = 0;
    while(i != EOF){
        i = fscanf(file, "   %d    %d", &start[index], &end[index]);
        index = index + 1;
    }
    clock_t begin = clock();


    int maxCounter = max_common_intervals(start,end,index-1);
    printf("The maximum number of intervals: %d\n", maxCounter);
    clock_t stop = clock();
    printf("Execution time: %fs\n", (double)(stop - begin)/CLOCKS_PER_SEC);

    fclose(file);
}
