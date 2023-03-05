#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main4() {
    char input[80];
    char *command, *arg;
    char *args[10];
    int i, num_args = 0;

    printf("$ ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // remove trailing newline

    command = strtok(input, " "); // extract first token as command

    // extract remaining tokens as arguments
    while ((arg = strtok(NULL, " ")) != NULL) {
        args[num_args++] = arg;
    }

    printf("Command: %s\n", command);
    printf("Arguments:\n");
    for (i = 0; i < num_args; i++) {
        printf("%d: %s\n", i+1, args[i]);
    }

    return 0;
}
