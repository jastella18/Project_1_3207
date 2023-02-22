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

// Function to read and parse /proc/meminfo
void read_meminfo() {
    FILE* fp;
    char buffer[BUFFER_SIZE];

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Error opening /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    printf("\nMemory Information:\n");
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
        char name[BUFFER_SIZE];
        unsigned long long value;
        if (sscanf(buffer, "%[^:]: %llu kB\n", name, &value) == 2) {
            printf("%s: %.2f MB\n", name, (double)value / 1024);
        }
    }

    fclose(fp);
}

int main() {
    read_cpuinfo();
    read_meminfo();
    return 0;
}