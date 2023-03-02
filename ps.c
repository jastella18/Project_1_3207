#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char path[100];
    FILE *fp;
    char line[1000];

    // Default values of arguments
    int pid = -1; // Display information for all processes
    int show_state = 0;
    int show_utime = 1;
    int show_stime = 0;
    int show_vmem = 0;
    int show_cmdline = 1;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        switch (argv[i][1]) {
            case 'p':
                pid = atoi(argv[++i]);
                break;
            case 's':
                show_state = 1;
                break;
            case 'U':
                show_utime = 0;
                break;
            case 'S':
                show_stime = 1;
                break;
            case 'v':
                show_vmem = 1;
                break;
            case 'c':
                show_cmdline = 0;
                break;
            default:
                printf("Unknown option: %s\n", argv[i]);
                return 1;
        }
    }

    printf("%-8s %-8s %-8s", "PID", "STATE", "CMDLINE");
    if (show_utime) {
        printf(" %-8s", "UTIME");
    }
    if (show_stime) {
        printf(" %-8s", "STIME");
    }
    if (show_vmem) {
        printf(" %-8s", "VMEM");
    }
    printf("\n");

    // Open directory /proc and read its contents
    if ((fp = fopen("/proc", "r")) == NULL) {
        printf("Error: cannot open /proc\n");
        return 1;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Check if the directory entry is a process ID
        if (sscanf(line, "%d", &pid) == 1) {
            sprintf(path, "/proc/%d/stat", pid);
            fp = fopen(path, "r");
            if (fp != NULL) {
                int pid_;
                char state;
                char cmdline[1000];
                unsigned long utime;
                unsigned long stime;
                unsigned long vmem;
                fscanf(fp, "%d %s %c", &pid_, cmdline, &state);
                if (pid == -1 || pid_ == pid) {
                    printf("%-8d %-8c ", pid_, state);
                    if (show_cmdline) {
                        printf("%-8s", cmdline);
                    }
                    if (show_utime) {
                        fscanf(fp, "%lu", &utime);
                        printf(" %-8lu", utime);
                    }
                    if (show_stime) {
                        fscanf(fp, "%lu", &stime);
                        printf(" %-8lu", stime);
                    }
                    if (show_vmem) {
                        sprintf(path, "/proc/%d/statm", pid_);
                        fp = fopen(path, "r");
                        if (fp != NULL) {
                            fscanf(fp, "%lu", &vmem);
                            printf(" %-8lu", vmem);
                            fclose(fp);
                        }
                    }
                    printf("\n");
                }
                fclose(fp);
            }
        }
    }
    fclose(fp);

    return 0;
}