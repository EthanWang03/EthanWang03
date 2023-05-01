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

int main(){
    FILE *file;
    char pattern[100];
    char *contents;
    int count = 0;
    int shiftCount = 0;
    long size;
        
    printf("Pattern to search for: ");
    fgets(pattern,100,stdin);
    pattern[strlen(pattern)-1] = '\0';


    file = fopen("data_A3_Q2.txt","r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    contents = (char *) malloc(size + 1);

    if(contents == NULL) {
        printf("Error!");   
        return 0; 
    }

    fseek(file, 0, SEEK_SET);

    int patternLen = strlen(pattern);

    clock_t start = clock();

    //read file
    while(fgets(contents, 255, file) != NULL){

        int stringLen = strlen(contents);

        //scan through string using forloop
        for(int i = 0; i <= stringLen - patternLen; i++) {
            int match = 1;
            for(int j = 0; j < patternLen; j++) {
                //if char is not a match set match to 0
                if(contents[i+j] != pattern[j]) {
                    match = 0;
                    break;
                }
                
            }
            //if all chars are matches match variable will remain 1
            if(match){
                count++;
                //shiftCount = i;
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