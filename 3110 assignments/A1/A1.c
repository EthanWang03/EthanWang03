#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

//function for printing ascii value of file
void ascii(int file, int length, unsigned char * buffer, char filename[]){
    //counter for length of file
    int bytesRead;
    char input[2];

    //printf \n
    if(write(STDOUT_FILENO, "\n", 1) != 1){
        fprintf(stderr, "write error\n");
        return;
    }
    while ((bytesRead = read(file, buffer, length)) > 0){

        for (int i = 0; i < bytesRead; i++) {

            //0x0 - 0x9 or 0xB - 0x1F
            if ((0 <= buffer[i] && buffer[i] <= 9) ||(11 <= buffer[i] && buffer[i] <= 31)) {
                //print ascii 0x20
                if(write(1, " ", 1) != 1){
                    //check for write error
                    fprintf(stderr, "write error\n");
                    return;
                }
            }

            //0x7F or greater
            else if(127 <= buffer[i] ){
                //print ascii 0x3F
                if(write(1, "?", 1) != 1){
                    //check for write error
                    fprintf(stderr, "write error\n");
                    return;
                }
            }

            //print ascii
            else{
                if(write(1, &buffer[i], 1) != 1){
                    //check for write error
                    fprintf(stderr, "write error\n");
                    return;
                }
            }
        }
    }

    //if bytesRead == -1
    if (bytesRead < 0){
        //check for read error
        fprintf(stderr, "read error from %s\n", filename);
        return;
    }
    //printf \n
    if(write(STDOUT_FILENO, "\n", 1) != 1){
        fprintf(stderr, "write error\n");
        return;
    }

    //exit statements
    printf("\n'm' for menu\n");
    printf("'x' for exit\n");
    while(1){
        if(scanf("%s", input) != 1){
            fprintf(stderr, "enter a valid input\n");
        }
        if(input[0] == 'm' || input[0] == 'M'){
            close(file);
            free(buffer);
            return;
        }
        else if(input[0] == 'x' || input[0] == 'X'){
            close(file);
            free(buffer);
            exit(0);
        }
        else{
            fprintf(stderr, "enter a valid input\n");
        }
    }
}

//function for printing hex value of file
void hex(int file, int length, unsigned char * buffer, char filename[]){
    //counter for length of file
    int bytesRead;
    char input[2];

    //printf \n
    if(write(STDOUT_FILENO, "\n", 1) != 1){
        fprintf(stderr, "write error\n");
        return;
    }
    
    while ((bytesRead = read(file, buffer, length)) > 0){
        for (int i = 0; i < bytesRead; i++) {
            char index[8];
            //print index for start
            if(i == 0 || i % 16 == 0){
                if(write(STDOUT_FILENO, "\n", 1) != 1){
                    fprintf(stderr, "write error\n");
                    return;
                }
                //convert to 7 digit hex to print
                sprintf(index, "%07x", i);
                if(write(1, index, 7) != 7){
                //check for write error
                    fprintf(stderr, "write error\n");
                    return;
                }
                //print space
                if(write(STDOUT_FILENO, " ", 1) != 1){
                    fprintf(stderr, "write error\n");
                    return;
                }
            }
            //print space every 8
            if(i % 8 == 0){
                if(write(STDOUT_FILENO, " ", 1) != 1){
                    fprintf(stderr, "write error\n");
                    return;
                }
            }
            char hex[3];
            //convert to hex
            sprintf(hex, "%02x", buffer[i]);
            if(write(1, hex, 2) != 2){
                //check for write error
                fprintf(stderr, "write error\n");
                return;
            }
            //print space
            if(write(STDOUT_FILENO, " ", 1) != 1){
                fprintf(stderr, "write error\n");
                return;
            }
            //print final index
            if(i == bytesRead - 1){
                //adjust for last i++
                i = i + 1;
                if(write(STDOUT_FILENO, "\n", 1) != 1){
                    fprintf(stderr, "write error\n");
                    return;
                }
                //convert to 7 digit hex to print
                sprintf(index, "%07x", i);
                if(write(1, index, 7) != 7){
                //check for write error
                    fprintf(stderr, "write error\n");
                    return;
                }
            }
        }
    }
    //if bytesRead == -1
    if (bytesRead < 0){
        //check for read error
        fprintf(stderr, "read error from %s\n", filename);
        return;
    }
    //printf \n
    if(write(STDOUT_FILENO, "\n", 1) != 1){
        fprintf(stderr, "write error\n");
        return;
    }

    //exit statements
    printf("\n'm' for menu\n");
    printf("'x' for exit\n");
    while(1){
        if(scanf("%s", input) != 1){
            fprintf(stderr, "enter a valid input\n");
        }
        if(input[0] == 'm' || input[0] == 'M'){
         close(file);
         free(buffer);
         return;
        }
        else if(input[0] == 'x' || input[0] == 'X'){
            close(file);
            free(buffer);
            exit(0);
        }
        else{
            fprintf(stderr, "enter a valid input\n");
        }
    }
}
int main(void){
    char mode = 'a';
    char input[2];
    int file;
    while(1){
        printf("\n=============A1=============\n");
        if(mode == 'a'){
            printf("current mode is ASCII\n");
        }
        else{
            printf("current mode is HEX\n");
        }
        printf("'o' to enter a file name\n");
        printf("'d' to select display mode\n");
        printf("'x' to exit\n");
        if(scanf("%s", input) != 1){
            fprintf(stderr, "enter a valid input\n");
        }
        if(input[0] == 'o' || input[0] == 'O'){

            char filename[100];
            unsigned char *buffer;

            printf("enter filename: ");
            scanf("%s", filename);
            //open file as read only
            file = open(filename, O_RDONLY);
            if (file < 0){
                fprintf(stderr, "Could not open file %s\n", filename);
            }
            //if file is valid
            else{
                //Get file size by seeking to the end of it
                int length = lseek(file, 0, SEEK_END);
                //seek back to start
                lseek(file, 0, SEEK_SET);

                //malloc buffer to be the size of the file length
                buffer = (unsigned char*)malloc(sizeof(unsigned char)*length);

                if(mode == 'a'){
                    ascii(file,length,buffer,filename);
                }
                else if(mode == 'h'){
                    hex(file,length,buffer,filename);
                }
            }
        }
        else if(input[0] == 'd'|| input[0] == 'D'){
            printf("'a' for ASCII\n");
            printf("'h' for HEX\n");
            if(scanf("%s", input) != 1){
                fprintf(stderr, "enter a valid input\n");
            }
            if(input[0] == 'a'|| input[0] == 'A'){
                mode = 'a';
            }
            else if(input[0] == 'h'|| input[0] == 'H'){
                mode = 'h';
            }
            else{
                fprintf(stderr, "enter a valid input\n");
            }
        }
        else if(input[0] == 'x'|| input[0] == 'X'){
            exit(0); 
        }
        else{
            fprintf(stderr, "enter a valid input\n");
        }
    }
}