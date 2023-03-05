#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024

int main(int argc, char *argv[]) {
    int timeout = 0;

    if (argc < 3) {
        printf("Usage: mytimeout.x <timeout> <command> [args]\n");
        return 1;
    }

    timeout = atoi(argv[1]);
    if (timeout <= 0) {
        printf("Timeout value must be a positive integer.\n");
        return 1;
    }

    char command[MAX_CMD_LENGTH] = {0};
    for (int i = 2; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }

    pid_t pid = fork();
    if (pid == 0) {
        /* Child process */
        system(command);
        exit(0);
    } else if (pid > 0) {
        /* Parent process */
        signal(SIGALRM, SIG_IGN);  /* Disable alarm signal while waiting for child process */
        alarm(timeout);  /* Set timeout */
        int status;
        pid_t result = wait(&status);  /* Wait for child process to finish */
        if (result == -1) {
            perror("wait");
            return 1;
        } else {
            alarm(0);  /* Disable alarm signal after child process finishes */
            if (WIFEXITED(status)) {
                printf("Command exited with status %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Command was terminated by signal %d\n", WTERMSIG(status));
            }
            return 0;
        }
    } else {
        /* Fork error */
        perror("fork");
        return 1;
    }
}
