#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 100

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    write(STDOUT_FILENO, "error\n", 6);
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *heap_start = sbrk(256);

  struct header *block1 = (struct header *)heap_start;
  block1->size = 128;
  block1->next = NULL;

  struct header *block2 = (struct header *)((char *)heap_start + 128);
  block2->size = 128;
  block2->next = block1;

  memset(block1 + 1, 0, 112);
  memset(block2 + 1, 1, 112);

  print_out("first block:       %p\n", &block1, sizeof(&block1));
  print_out("second block:      %p\n", &block2, sizeof(&block2));

  print_out("first block size:  %lu\n", &block1->size, sizeof(uint64_t));
  print_out("first block next:  %p\n", &block1->next, sizeof(&block1->next));
  print_out("second block size: %lu\n", &block2->size, sizeof(uint64_t));
  print_out("second block next: %p\n", &block2->next, sizeof(&block2->next));

  char *data1 = (char *)(block1 + 1);
  for (int i = 0; i < 112; i++) {
    print_out("%d\n", &data1[i], sizeof(uint64_t));
  }

  char *data2 = (char *)(block2 + 1);
  for (int i = 0; i < 112; i++) {
    uint64_t val = (uint8_t)data2[i];
    print_out("%d\n", &val, sizeof(uint64_t));
  }

  return 0;
}
