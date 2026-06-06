#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HISTORY_SIZE 5

void add_to_history(char *history[], int *count, char *input) {
  if (*count == HISTORY_SIZE) {
    free(history[0]);
    for (int i = 0; i < HISTORY_SIZE - 1; i++) {
      history[i] = history[i + 1];
    }
    history[HISTORY_SIZE - 1] = input;
  } else {
    history[*count] = input;
    (*count)++;
  }
}

void print_history(char *history[], int count) {
  for (int i = 0; i < count; i++) {
    printf("%s", history[i]);
  }
}

int main(void) {
  char *history[HISTORY_SIZE] = {NULL};
  int count = 0;
  char *buf = NULL;
  size_t bufsize = 0;

  while (1) {
    printf("Enter input: ");
    ssize_t chars = getline(&buf, &bufsize, stdin);
    if (chars < 0) {
      break;
    }

    char *input = strdup(buf);

    if (strncmp(input, "print\n", 6) == 0) {
      add_to_history(history, &count, input);
      print_history(history, count);
    } else {
      add_to_history(history, &count, input);
    }
  }

  for (int i = 0; i < count; i++) {
    free(history[i]);
  }
  free(buf);
  return 0;
}
