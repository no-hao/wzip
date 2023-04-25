#include "../include/file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

// Closes a file using its file descriptor, ensuring no resources are leaked
// The function uses the close system call to close the file and handle any
// errors that may occur
void close_file(int fd) {
  if (close(fd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

// Retrieves the size of a file using its file descriptor
// function uses fstat to gather file info and extracts the file size from it
size_t get_file_size(int fd) {
  struct stat st;
  if (fstat(fd, &st) == -1) {
    perror("fstat");
    exit(EXIT_FAILURE);
  }
  return st.st_size;
}

// Maps a file into memory for more efficient file manipulation
// The function uses mmap to map the file into memory and returns a pointer to
// the mapped file
char *mmap_file(int fd, size_t file_size) {
  char *src = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (src == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }
  return src;
}

// Unmaps a previously memory-mapped file to free up system resources
// The function uses munmap to unmap the file and clean up resources
void unmap_file(char *src, size_t file_size) {
  if (munmap(src, file_size) == -1) {
    perror("munmap");
    exit(EXIT_FAILURE);
  }
}
