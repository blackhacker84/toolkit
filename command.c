#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ARGS 10
#define MAX_PIPES 10

// Parse the input string to extract the command and its arguments
void parse_input(char *input, char **command, char **args) {
    int i = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL) {
        if (i == 0) {
            *command = token;
        } else {
            args[i-1] = token;
        }
        token = strtok(NULL, " \t\n");
        i++;
    }
    args[i-1] = NULL;
}

// Implementation of myexit command
void myexit() {
    exit(0);
}

// Implementation of mycd command
void mycd(char **args) {
    if (args[0] == NULL) {
        // No directory specified, go to home directory
        chdir(getenv("HOME"));
    } else {
        if (chdir(args[0]) == -1) {
            printf("cd: %s: No such file or directory\n", args[0]);
        }
    }
}

// Implementation of mypwd command
void mypwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}

int main2() {
    char input[1024];
    char *command, *args[MAX_ARGS];

    while (1) {
        // Print prompt and read input
        printf("$ ");
        fgets(input, sizeof(input), stdin);

        // Parse input
        parse_input(input, &command, args);

        // Execute command
        if (strcmp(command, "myexit") == 0) {
            myexit();
        } else if (strcmp(command, "mycd") == 0) {
            mycd(args);
        } else if (strcmp(command, "mypwd") == 0) {
            mypwd();
        } else {
            printf("Command not found\n");
        }
    }

    return 0;
}

