#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd_in = open("input.txt", O_RDONLY);
    if (fd_in == -1) {
        perror("Error opening file");
        exit(1);
    }

    if (dup2(fd_in, STDIN_FILENO) == -1) {
        perror("Error redirecting input");
        exit(1);
    }

    close(fd_in);

    // Now any read from standard input will come from input.txt
    // For example:
    char buffer[256];
    fgets(buffer, 256, stdin);
    printf("Read from file: %s", buffer);

    return 0;
}
