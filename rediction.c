#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_FILENAME_LEN 256

int main(int argc, char *argv[]) {
    char *args[MAX_ARGS]; // array to hold command-line arguments
    char input_file[MAX_FILENAME_LEN]; // buffer to hold input file name
    char output_file[MAX_FILENAME_LEN]; // buffer to hold output file name
    int input_redirect = 0; // flag to indicate input redirection
    int output_redirect = 0; // flag to indicate output redirection
    int i;

    // parse command-line arguments
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "<") == 0) { // input redirection
            if (i + 1 < argc) {
                strncpy(input_file, argv[i+1], MAX_FILENAME_LEN);
                input_redirect = 1;
                i++; // skip over the file name
            } else {
                fprintf(stderr, "Error: No input file specified\n");
                return 1;
            }
        } else if (strcmp(argv[i], ">") == 0) { // output redirection
            if (i + 1 < argc) {
                strncpy(output_file, argv[i+1], MAX_FILENAME_LEN);
                output_redirect = 1;
                i++; // skip over the file name
            } else {
                fprintf(stderr, "Error: No output file specified\n");
                return 1;
            }
        } else { // regular argument
            args[i-1] = argv[i];
        }
    }
    args[i-1] = NULL; // terminate the argument list with NULL

    // redirect input if necessary
    if (input_redirect) {
        FILE *fp = fopen(input_file, "r");
        if (!fp) {
            fprintf(stderr, "Error: Failed to open input file %s\n", input_file);
            return 1;
        }
        if (dup2(fileno(fp), STDIN_FILENO) == -1) {
            fprintf(stderr, "Error: Failed to redirect input\n");
            return 1;
        }
        fclose(fp);
    }

    // redirect output if necessary
    if (output_redirect) {
        FILE *fp = fopen(output_file, "w");
        if (!fp) {
            fprintf(stderr, "Error: Failed to open output file %s\n", output_file);
            return 1;
        }
        if (dup2(fileno(fp), STDOUT_FILENO) == -1) {
            fprintf(stderr, "Error: Failed to redirect output\n");
            return 1;
        }
        fclose(fp);
    }

    // execute the command
    execvp(args[0], args);
    fprintf(stderr, "Error: Failed to execute command %s\n", args[0]);
    return 1;
}
