#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer[1024];
    FILE* pipe = popen("ps aux", "r");
    if (!pipe) {
        perror("Error opening pipe");
        return 1;
    }
    printf("Process List:\n");
    while (fgets(buffer, sizeof(buffer), pipe)) {
        printf("%s", buffer);
    }
    pclose(pipe);
    return 0;
}