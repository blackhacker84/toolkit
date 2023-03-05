#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myexit() {
    exit(0);
}

void mycd(char* path) {
    int result = chdir(path);
    if (result == -1) {
        perror("mytoolkit");
    }
}

void mypwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("mytoolkit");
    }
}
