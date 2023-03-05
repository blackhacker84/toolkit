#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 20  // maximum number of arguments in a command line
#define MAX_PIPES 5  // maximum number of pipes in a command line

int main6() {
    char input[80];  // buffer to hold user input
    char *args[MAX_ARGS];  // array to hold command arguments
    int num_pipes;  // number of pipes in command line
    int i;  // loop counter
    
    // set up the command prompt
    while (1) {
        printf("$ ");
        
        // read input from user
        fgets(input, 80, stdin);
        
        // remove newline character from input
        input[strcspn(input, "\n")] = '\0';
        
        // parse input into command arguments
        num_pipes = 0;
        args[0] = strtok(input, " ");
        for (i = 1; i < MAX_ARGS; i++) {
            args[i] = strtok(NULL, " ");
            if (args[i] == NULL) {
                break;
            } else if (strcmp(args[i], "|") == 0) {
                num_pipes++;
            }
        }
        args[i] = NULL;  // set last argument to NULL
        
        // check if command is empty
        if (args[0] == NULL) {
            continue;
        }
        
        // process command
        if (strcmp(args[0], "myexit") == 0) {
            // terminate the toolkit
            exit(0);
        } else if (strcmp(args[0], "mycd") == 0) {
            // change the current working directory
            if (chdir(args[1]) != 0) {
                printf("mytoolkit: %s: No such file or directory\n", args[1]);
            }
        } else if (strcmp(args[0], "mypwd") == 0) {
            // print the current working directory
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd() error");
            }
        } else {
            // external command
            // TODO: implement external command execution
            printf("mytoolkit: %s: command not found\n", args[0]);
        }
    }
}
