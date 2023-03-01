#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

// Function to read and parse /proc/cpuinfo
void read_cpuinfo() {
    FILE* fp;
    char buffer[BUFFER_SIZE];

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        perror("Error opening /proc/cpuinfo");
        exit(EXIT_FAILURE);
    }

    printf("CPU Information:\n");
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char name[BUFFER_SIZE], value[BUFFER_SIZE];
        if (sscanf(buffer, "%[^:]: %[^\n]\n", name, value) == 2) {
            printf("%s: %s\n", name, value);
        }
    }

    fclose(fp);
}


int main() {
    read_cpuinfo();
    return 0;
}