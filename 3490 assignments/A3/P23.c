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

#define ALPHABET_SIZE 256

//returns greater number
int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

//preprocessing
void badCharTable(char pattern[], int badChar[]){

    int patternLen = strlen(pattern);

    //initialize to -1
    for(int i = 0; i < ALPHABET_SIZE; i++){
        badChar[i] = patternLen;
    }

    //fill with last occurance of char
    for(int i = 0; i < patternLen; i++){
        badChar[(int)pattern[i]] = patternLen - i - 1;
    }
}

//preprocessing find suffix table
void suffixes(char *pattern, int patternLen, int *suff) {
    int f;
    int g;
    int i;
    
    suff[patternLen - 1] = patternLen;
    g = patternLen - 1;

    //compute the suffixes of the pattern in reverse order and store them in the suff array.
    for (i = patternLen - 2; i >= 0; --i) {
        if (i > g && suff[i + patternLen - 1 - f] < i - g)
            suff[i] = suff[i + patternLen - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + patternLen - 1 - f])
                g = g - 1;
            suff[i] = f - g;
        }
    }
}

void suffixTableCreate(char *pattern, int patternLen, int suffixTable[]) {
    int i;
    int j;
    int suff[patternLen];
    
    //compute the suffixes of the pattern and store them in the suff array
    suffixes(pattern, patternLen, suff);
    
    //initialize suffTable
    for(i = 0; i < patternLen; ++i){
        suffixTable[i] = patternLen;
    }
    //For each element in the suff array that is equal to i + 1
    //set the elements in the suffixTable array to be patternLen - 1 - i
    for(i = patternLen - 1; i >= 0; --i){
        if(suff[i] == i + 1){
            for(j = 0; j < patternLen - 1 - i; ++j){
                if (suffixTable[j] == patternLen){
                    suffixTable[j] = patternLen - 1 - i;
                }
            }
        }
    }
    for (i = 0; i <= patternLen - 2; ++i){
        suffixTable[patternLen - 1 - suff[i]] = patternLen - 1 - i;
    }
}


int main(){
    FILE *file;
    char pattern[100];
    int suffixTable[100];
    char *contents;
    int count = 0;
    int shifts = 0;
    int shiftCount = 0;
    long size;
    int badChar[ALPHABET_SIZE];
    int s = 0;
    
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

    clock_t start = clock();

    //Preprocessing for bad character heuristic
    badCharTable(pattern, badChar);
    suffixTableCreate(pattern, strlen(pattern), suffixTable);

    int patternLen = strlen(pattern);

    //read file
    while(fgets(contents, size, file) != NULL){

        int stringLen = strlen(contents);
        s = 0;
        
        while(s <= (stringLen - patternLen)){
            int j = patternLen - 1;

            //keep reducing patternLen while characters of pattern match with the text
            while(j >= 0 && pattern[j] == contents[s + j]){
                j = j - 1;
            }

            //if the pattern is found in current shift j will become -1 after loop
            if(j < 0){
                count = count + 1;
                s += suffixTable[0];
            }

            //skip elements based off of badChar and suffixTable
            else{
                int shift = suffixTable[j]; 
                int badCharShift = badChar[(int)contents[s + j]] - patternLen + j + 1;
                if(shifts > badCharShift){
                    s += shift;
                }
                else{
                    s += badCharShift;
                }
            }
            shiftCount = shiftCount + 1;
        }
    }

    clock_t stop = clock();

    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shiftCount);
    printf("Execution time: %fs\n", (double)(stop - start)/CLOCKS_PER_SEC);

    free(contents);
    fclose(file);
    return 0;
}