#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>


void print_status(long tgid) {
  char path[40], line[100], *p;
  char name[100];
  FILE* statusf;

  snprintf(path, 40, "/proc/%ld/status", tgid);

  statusf = fopen(path, "r");
  if (!statusf) return;

  strcpy(name, fgets(line, 100, statusf));
  while (fgets(line, 100, statusf)) {
    if (strncmp(line, "VmRSS:", 6) != 0) continue;
    p = line + 7;
    while (isspace(*p)) ++p;

    char *size_vrss = strtok(p, " ");
    int size_vrss_int = atoi(size_vrss);
    if(size_vrss_int > 10000) {
      printf("%s",name);
      printf("Pid:\t%ld\n",tgid);
      printf("Memory Used: %s kB\n\n", size_vrss);
    }
    break;
  }

  fclose(statusf);
}

int main() {
  DIR* proc = opendir("/proc");
  struct dirent* ent;
  long tgid;

  if (proc == NULL) {
    perror("opendir(/proc)");
    return 1;
  }
  ent = readdir(proc);
  while (ent != NULL) {
    if (!isdigit(*ent->d_name)) continue;

    tgid = strtol(ent->d_name, NULL, 10);

    print_status(tgid);

    ent= readdir(proc);
  }
  closedir(proc);
}