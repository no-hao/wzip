#ifndef FILE_IO_H
#define FILE_IO_H

#include <stddef.h>

// Closes a file given a file descriptor
// fd: The file descriptor of the file
void close_file(int fd);

// Gets the size of a file given a file descriptor
// fd: The file descriptor of the file
// Returns: The size of the file in bytes
size_t get_file_size(int fd);

// Maps a file into memory
// fd: The file descriptor of the file
// file_size: The size of the file in bytes
// Returns: A pointer to the memory-mapped file
char *mmap_file(int fd, size_t file_size);

// Unmaps a memory-mapped file
// src: Pointer to the memory-mapped file
// file_size: The size of the file in bytes
void unmap_file(char *src, size_t file_size);

#endif
