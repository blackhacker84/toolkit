#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd_out = open("output.txt", O_WRONLY | O_CREAT, 0644);
    if (fd_out == -1) {
        perror("Error opening file");
        exit(1);
    }

    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        perror("Error redirecting output");
        exit(1);
    }

    close(fd_out);

    // Now any write to standard output will go to output.txt
    // For example:
    printf("This will be written to file.\n");

    return 0;
}
