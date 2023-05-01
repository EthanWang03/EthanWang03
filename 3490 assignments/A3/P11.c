/*
Ethan Wang
1184940
A3 cis 3490
March 10 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Define a struct to represent intervals
typedef struct {
    int start;
    int end;
} interval;

//compare for qsort
int cmp(const void *a, const void *b) {
    interval *ia = (interval *)a;
    interval *ib = (interval *)b;

    if(ia->start > ib->start){
        return 1;
    }
    else if(ia->start < ib->start){
        return -1;
    }
    else{
        return 0;
    }
}

int max_common_intervals(interval *intervals, int n) {
    // Sort the intervals by their start points

    qsort(intervals, n, sizeof(interval), cmp);
    
    int maxCounter = 0;
    int count;
    int commonIndex = 0;

    //search through all points between first start and last end
    for(int i = intervals[0].start; i < intervals[n-1].start; i++){
        count = 0;
        //seach through all points
        for(int k = 0; k < n; k++){
            //if point is inbetween start and end add to count
            if((i > intervals[k].start) && (i < intervals[k].end)) {
                count++;
            }
        }
        //find include point
        if(count > maxCounter) {
            maxCounter = count;
            commonIndex = i;
        }
    }

    printf("The intverals include point: %d\n",commonIndex);
    return maxCounter;
}

int main(){
    char filename[100];
    FILE *file;
    printf("Enter filename: ");
    scanf(" %s", filename);

    interval *intervals = (interval *)malloc(30000 * sizeof(interval));

    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }
    int i;
    int index = 0;
    while(i != EOF){
        i = fscanf(file, "   %d    %d", &intervals[index].start, &intervals[index].end);
        index = index + 1;
    }
    clock_t start = clock();
    int maxCounter = max_common_intervals(intervals, index-1);
    printf("the maximum number of intervals: %d\n", maxCounter);
    clock_t stop = clock();
    printf("Execution time: %fs\n", (double)(stop - start)/CLOCKS_PER_SEC);
    
    free(intervals);
    fclose(file);

    return 0;
}