#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>

void sigchld_handler(int signum) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
       printf("Caught SIGCHLD signal for child process %d\n", pid);
        if (WIFEXITED(status)) {
            printf("Child process %d exited normally with status %d\n", pid, WEXITSTATUS(status));
        }else{
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
    signal(SIGCHLD, sigchld_handler);
}

int main(int argc, char *argv[]){
    int pipefd[argc-1][2];
    pid_t pid;
    char *buffer;
    int counts[26] = {0};

    signal(SIGCHLD, sigchld_handler);

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

        pid = fork();

        //check for fork error
        if(pid == -1){
            fprintf(stderr, "Fork failed\n");
            exit(EXIT_FAILURE); //1
        }

        //child process
        if(pid == 0){
            //close read
            close(pipefd[i-1][0]);

            //open file
            int file = open(argv[i], O_RDONLY);

            //check for file open error
            if(file == -1) {
                fprintf(stderr, "Error opening file: %s\n", argv[i]);
                close(pipefd[i-1][1]);
                exit(EXIT_FAILURE); //1
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
                    exit(EXIT_FAILURE); //1
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
                    exit(EXIT_FAILURE); //1
                }
                free(buffer);
                close(pipefd[i-1][1]);
                //sleep(10+2*(i-1));
                exit(EXIT_SUCCESS); //0
            }
        }
        //parent process
        else{
            close(pipefd[i-1][1]);
            int counts[26] = {0};
            //fprintf(stderr, "reading\n");
            if(read(pipefd[i-1][0], counts, sizeof(counts)) == -1){
                fprintf(stderr, "Error reading pipe: %s\n", argv[i]);
                exit(EXIT_FAILURE); //1
            }
            printf("Letter counts:\n");
            for(int j = 0; j < 26; j++) {
                printf("%c: %d\n", 'a' + j, counts[j]);
            }
        }
    }
    // parent process waits for SIGCHLD signal
    while(1){
        sleep(10);
    }
    return 0;
}