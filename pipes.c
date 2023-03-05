#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 20

int main()
{
    char command[100];
    char *args[MAX_ARGS];
    int pipes[2];
    int fd_in = 0;
    int fd_out;
    pid_t pid;
    
    while (1) {
        printf("$ ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // remove trailing newline
        
        int i = 0;
        args[i] = strtok(command, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;
        
        int pipe_count = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(args[j], "|") == 0) {
                pipe_count++;
            }
        }
        
        fd_out = 1; // set stdout as default output
        
        for (int j = 0; j <= pipe_count; j++) {
            pipe(pipes);
            pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                if (j != 0) {
                    dup2(fd_in, 0);
                    close(fd_in);
                }
                if (j != pipe_count) {
                    dup2(pipes[1], 1);
                    close(pipes[1]);
                }
                execvp(args[0], args);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
                close(pipes[1]);
                fd_in = pipes[0];
            }
        }
    }
    
    return 0;
}

