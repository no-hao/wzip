#ifndef FILE_IO_H
#define FILE_IO_H

#include <stddef.h>

void unmap_file(char *src, size_t file_size);

char *mmap_file(int fd, size_t file_size);

size_t get_file_size(int fd);

void close_file(int fd);

#endif
