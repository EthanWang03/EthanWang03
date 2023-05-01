#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

//debug to check for normal exit
int debug = 0;

void SIGCHLDHANDLER(int signum){
    int status;
    pid_t pid;

    //reinstall
    signal(SIGCHLD, SIGCHLDHANDLER);

    while((pid = waitpid(-1, &status, WNOHANG)) > 0){

        //print catch and pid
        printf("Caught SIGCHLD signal for child process %d\n", pid);
        
        //normal exit
        if(status == 0){
            // child process terminated normally
            //printf("Child process %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
            debug = 0;
        }

        //error exit
        else if(status != 0){
            //printf("Child process %d terminated abmormally with exit status %d\n", pid, WEXITSTATUS(status));
            debug = 1;
        }
        
        //catch signal kill
        if(WTERMSIG(status) == SIGINT){
            // child process terminated due to a signal
            printf("Child process %d terminated due to signal %s\n", pid, strsignal(status));
        }
    }
}

int main(int argc, char *argv[]){
    int pipefd[argc-1][2];
    pid_t pid;
    char *buffer;
    int counts[26] = {0};    

    //call signal handler
    signal(SIGCHLD, SIGCHLDHANDLER);

    //check for no command line
    if(argc == 1){
        fprintf(stderr, "No files given\n");
        return 1;
    }

    //create pipe
    for(int i = 0; i < argc-1; i++){
        if(pipe(pipefd[i]) == -1) {
            fprintf(stderr, "Pipe failed\n");
            return 1;
        }
    }

    //loop through each file argument
    for(int i = 1; i < argc; i++){

        //filename = filename from command line
        char *filename = argv[i];

        pid = fork();

        //check for fork error
        if(pid == -1){
            fprintf(stderr, "Fork failed\n");
            exit(1);
        }

        //child process
        if(pid == 0){
            
            //close read
            close(pipefd[i-1][0]);

            //open file
            int file = open(filename, O_RDONLY);

            //check for file open error
            if(file < 0) {
                fprintf(stderr, "Error opening file: %s\n", filename);
                close(pipefd[i-1][1]);
                exit(1);
            }
            else{

                //Get file size by seeking to the end of it
                int length = lseek(file, 0, SEEK_END);
                //seek back to start
                lseek(file, 0, SEEK_SET);

                //malloc buffer to be the size of the file length
                buffer = (char*)malloc(sizeof(char)*length);

                if(read(file, buffer, length) == -1){
                    fprintf(stderr, "read error\n");
                    free(buffer);
                    close(pipefd[i-1][1]);
                    exit(1);
                }
                
                //compute histogram
                for(int j = 0; j < length; j++) {
                    if(isalpha(buffer[j])) { //check if the character is a letter
                        counts[tolower(buffer[j]) - 'a'] = counts[tolower(buffer[j]) - 'a'] + 1; //increment the count for the letter
                    }
                }
                //fprintf(stderr, "writing\n");
                if(write(pipefd[i-1][1], counts, sizeof(counts)) == -1){
                    fprintf(stderr, "Error writting pipe %d\n", i);
                    free(buffer);
                    close(pipefd[i-1][1]);
                    exit(1);
                }
                free(buffer);
                //free(filename);
                close(pipefd[i-1][1]);
                sleep(10+2*(i-1));
                exit(0);
            }
        }
        else{
            //int status;
            close(pipefd[i-1][1]);

            //printf("%d", getpid());

            if(strcmp(filename,"SIG") == 0){
                kill(pid, SIGINT);
                //printf("%d", getpid());
            }

            //wait until child finishes
            pause();

            //if child exited correctly
            if(debug == 0){  
                int counts[26] = {0};
                //fprintf(stderr, "reading\n");
                if(read(pipefd[i-1][0], counts, sizeof(counts)) == -1){
                    fprintf(stderr, "Error reading pipe: %s\n", filename);
                    return 1;
                }
                char writeFile[100] = "file";
                char filePID[10];

                //turn pid into string
                sprintf(filePID, "%d", pid);
                
                strcat(writeFile, filePID);
                strcat(writeFile, ".hist");
                
                //open file to write
                int file = open(writeFile, O_WRONLY | O_CREAT | O_TRUNC, 777);
                if(file < 0) {
                    fprintf(stderr, "Error opening file: %s\n", writeFile);
                    return 1;
                }

                char contents[10];
                int length;
                //write histogram into file
                for(int k = 0; k < 26; k++){
                    length = snprintf(contents, 1024, "%c: %d\n", 'a' + k, counts[k]);
                    if(write(file, contents, length) != length) {
                        fprintf(stderr, "Error writing to file: %s\n", writeFile);
                        return 1;
                    }
                }

                close(file);
            }
            //free(filename);
            close(pipefd[i-1][0]);
        }
    }

    //run for number of files specified
    int i = 0;
    while(i < argc-1){
        //pause();
        i = i + 1;
    }
    return 0;
}