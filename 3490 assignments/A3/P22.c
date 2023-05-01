/*
Ethan Wang
1184940
A3 cis 3490
March 10 2023
*/

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define MAX_CHARS 256

void precomputeShifts(char *pattern, int patternLen, int *shift_table) {
    
    //initialize shift table to default value
    for (int i = 0; i < MAX_CHARS; i++) {
        shift_table[i] = patternLen;
    }

    //precompute shifts for each character in the word
    for (int i = 0; i < patternLen - 1; i++) {
        shift_table[(int)pattern[i]] = patternLen - 1 - i;
    }
}

int main(){
    FILE *file;
    char pattern[100];
    char *contents;
    int count = 0;
    int shifts = 0;
    long size;
    
    //get user input
    printf("Pattern to search for: ");
    fgets(pattern,100,stdin);
    pattern[strlen(pattern)-1] = '\0';

    //open file
    file = fopen("data_A3_Q2.txt","r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);

    contents = (char *) malloc(size);

    if(contents == NULL) {
        printf("Error!");   
        return 0; 
    }

    fseek(file, 0, SEEK_SET);

    int patternLen = strlen(pattern);

    int shiftTable[MAX_CHARS];

    clock_t start = clock();
    
    //precompute the shift table for the word
    precomputeShifts(pattern, patternLen, shiftTable);

    //read file
    while(fgets(contents, 255, file) != NULL){

        int stringLen = strlen(contents);
        
        int i = patternLen - 1;

        //Search for occurrences of the word in the string
        while(i < stringLen){
            
            int k = i;
            int j = patternLen - 1;

            //search
            while(j >= 0 && pattern[j] == contents[k]){
                k = k - 1;
                j = j - 1;
            }
            if(j < 0){
                //Match found, increment count and move past the word
                count = count + 1;
                i = i + 1;
            }
            else{
                //No match, shift to the right using the shift table
                i += shiftTable[(int)contents[i]];
            }
            shifts = shifts + 1;
        }
    }

    clock_t stop = clock();

    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shifts);
    printf("Execution time: %fs\n", (double)(stop - start)/CLOCKS_PER_SEC);

    free(contents);
    fclose(file);
    return 0;
}