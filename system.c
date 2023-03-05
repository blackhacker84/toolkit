#include <stdlib.h>

int main() {
    char *command = "ls -la"; // Command to execute

    int status = system(command); // Execute command

    if (status == -1) {
        printf("Error executing command\n");
        return 1;
    }

    return 0;
}
