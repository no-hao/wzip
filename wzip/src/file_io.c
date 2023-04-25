#include "../include/file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

size_t get_file_size(int fd) {
  struct stat st;
  if (fstat(fd, &st) == -1) {
    perror("fstat");
    exit(EXIT_FAILURE);
  }
  return st.st_size;
}

char *mmap_file(int fd, size_t file_size) {
  char *src = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (src == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }
  return src;
}

void unmap_file(char *src, size_t file_size) {
  if (munmap(src, file_size) == -1) {
    perror("munmap");
    exit(EXIT_FAILURE);
  }
}

void close_file(int fd) {
  if (close(fd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}
