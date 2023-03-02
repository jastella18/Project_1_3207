#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char command[BUFFER_SIZE] = "ps -u $USER";
    char buffer[BUFFER_SIZE];
    FILE *pipe;

    // Process -p option
    if (argc >= 3 && strcmp(argv[1], "-p") == 0) {
        strcat(command, " -p ");
        strcat(command, argv[2]);
    }

    // Process -s option
    if (argc >= 2 && strcmp(argv[argc - 1], "-s") == 0) {
        strcat(command, " -o stat");
    }

    // Process -U option
    if (argc >= 2 && strcmp(argv[argc - 1], "-U") != 0) {
        strcat(command, " -o time");
    }

    // Process -S option
    if (argc >= 2 && strcmp(argv[argc - 1], "-S") == 0) {
        strcat(command, " -o stime");
    }

    // Process -v option
    if (argc >= 2 && strcmp(argv[argc - 1], "-v") == 0) {
        strcat(command, " -o vsz");
    }

    // Process -c option
    if (argc >= 2 && strcmp(argv[argc - 1], "-c") != 0) {
        strcat(command, " -o cmd");
    }

    // Open pipe and execute command
    pipe = popen(command, "r");
    if (!pipe) {
        perror("Error opening pipe");
        return 1;
    }

    // Read output from command and print to console
    printf("Process List:\n");
    while (fgets(buffer, BUFFER_SIZE, pipe)) {
        printf("%s", buffer);
    }

    // Close pipe and return
    pclose(pipe);
    return 0;
}