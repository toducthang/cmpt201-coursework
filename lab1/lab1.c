#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buf = NULL;
  size_t bufsize = 0;
  while (1) {
    printf("Please enter some text: ");
    ssize_t chars = getline(&buf, &bufsize, stdin);
    if (chars < 0) {
      perror("getline");
      free(buf);
      return 1;
    }

    printf("Tokens: \n");
    char *saveptr;
    char *token = strtok_r(buf, " \n", &saveptr);
    while (token != NULL) {
      printf(" %s\n", token);
      token = strtok_r(NULL, " \n", &saveptr);
    }
  }

  free(buf);
  return 0;
}
