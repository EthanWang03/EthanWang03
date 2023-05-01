//Based on Fig. 3.5 in "Advanced Programming in the UNIX Environment", 3rd ed. by R. Stevens and S. Rago
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

#define BUFFSIZE 4096

//Read the specified file, write to standard out
int main(void){
    int n;
    char *buf;
    int fd;
    char filename[] = "stuff.txt";

    fd = open(filename, O_RDONLY);
    if (fd < 0){
        fprintf(stderr, "Could not open file %s\n", filename);
    }
    
    //Get file size by seeking to the end of it
    int length = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    //malloc buf to be the size of the file length
    buf = (char*)malloc(sizeof(char)*length);

    while ((n = read(fd, buf, BUFFSIZE)) > 0){
        //printf("%d ",n);
        if (write(STDOUT_FILENO, buf, n) != n){
            fprintf(stderr, "write error");
        }if (n < 0){
            fprintf(stderr, "read error from %s\n", filename);
        }
    }
    printf("\n");

    close(fd);
    
    exit(0); 
}