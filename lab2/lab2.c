#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *buf = NULL;
  size_t bufsize = 0;

  while (1) {
    printf("Enter programs to run .\n");
    ssize_t chars = getline(&buf, &bufsize, stdin);
    if (chars < 0) {
      perror("getline");
      free(buf);
      return 1;
    }

    buf[strcspn(buf, "\n")] = 0;

    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      free(buf);
      return 1;
    }

    if (pid == 0) {
      execl(buf, buf, NULL);
      printf("Exec failure\n");
      exit(1);
    } else {
      waitpid(pid, NULL, 0);
    }

    free(buf);
    return 0;
  }
}
