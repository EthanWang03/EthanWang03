/*
Ethan Wang
1184940
A4 cis 3490
March 27 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
    char filename[100];// = "data_A4_Q2_2.txt";
    FILE *file;
    int size;

    //read file
    printf("Enter filename: ");
    scanf(" %s", filename);

    file = fopen(filename,"r");
    if(file == NULL){
        printf("Error!");   
        return 0;             
    }

    fscanf(file, "%d", &size);

    int menPref[size][size];
    int womenPref[size][size];
    int marriage[size][size];

    int men[size];
    int women[size];

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            fscanf(file, "%d", &menPref[i][j]);
        }
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            fscanf(file, "%d", &womenPref[i][j]);
        }
    }

    int man;
    int woman;
    
    //set all to free
    for(int i = 0; i < size; i++){
        men[i] = -1;
        women[i] = -1;
    }
    
    while(1){
        int freeManFound = 0;
        for(int i = 0; i < size; i++){

            //if man is free
            if(men[i] == -1){
                freeManFound = 1;
                man = i;
                break;
            }
        }

        //end loop if no more men are free
        if(freeManFound == 0){
            break;
        }

        //loop through men pref
        for(int i = 0; i < size && men[man] == -1; i++){

            //get womens index from mans pref
            woman = menPref[man][i] - 1;
            
            //if women is free
            if(women[woman] == -1){
                men[man] = woman;
                women[woman] = man;
            }
            else{
                int currentMan = women[woman];

                //loop through women pref
                for(int j = 0; j < size; j++){

                    //if women is higher on list
                    if(womenPref[woman][j] == currentMan + 1){
                        //women will stay with current man
                        break;
                    }

                    //if man is higher on list
                    if(womenPref[woman][j] == man + 1){
                        //free old women
                        men[currentMan] = -1;
                        men[man] = woman;
                        women[woman] = man;
                        break;
                    }
                }
            }
        }
    }

    //set all marriage to 0
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            marriage[i][j] = 0;
        }
    }

    //set final marriage values
    for(int i = 0; i < size; i++) {
        marriage[i][men[i]] = 1;
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            printf("%d ", marriage[i][j]);
        }
        printf("\n");
    }

    fclose(file);

    return 0;
}