#include <stdio.h>

int main() {
    printf("$ ");

    char input[81];
    while (fgets(input, 81, stdin) != NULL) {
        // Check for end-of-file character
        if (feof(stdin)) {
            break;
        }

        // Process input command
        // ...

        printf("$ ");
    }

    printf("\n");
    return 0;
}

