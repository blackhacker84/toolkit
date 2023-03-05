#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s snds cmd [cmd-args]\n", argv[0]);
        exit(1);
    }

    int seconds = atoi(argv[1]);
    if (seconds <= 0) {
        fprintf(stderr, "Invalid time limit: %s\n", argv[1]);
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Failed to fork process\n");
        exit(1);
    } else if (pid == 0) { // child process
        // execute the command using execvp
        char **cmd_args = &argv[2];
        execvp(cmd_args[0], cmd_args);
        // execvp only returns if there is an error
        fprintf(stderr, "Failed to execute command: %s\n", cmd_args[0]);
        exit(1);
    } else { // parent process
        // wait for the child process to terminate or for the timeout to expire
        sleep(seconds);
        int status;
        pid_t result = waitpid(pid, &status, WNOHANG);
        if (result == 0) {
            // child process is still running, kill it
            if (kill(pid, SIGTERM) < 0) {
                fprintf(stderr, "Failed to terminate process: %d\n", pid);
                exit(1);
            }
            // wait for the child process to terminate
            result = waitpid(pid, &status, 0);
            if (result < 0) {
                fprintf(stderr, "Failed to wait for process: %d\n", pid);
                exit(1);
            }
        }
        // exit with the same status as the child process
        if (WIFEXITED(status)) {
            exit(WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            exit(128 + WTERMSIG(status));
        } else {
            exit(1);
        }
    }
}
