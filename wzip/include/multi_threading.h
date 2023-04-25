#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include "../include/wzip_helper.h"

// Adjusts the starting points of regions to prevent incorrect compression
// src: Pointer to the memory-mapped file
// file_size: The size of the file in bytes
// region_starts: Array of starting points for each region
void adjust_region_starts(char *src, size_t file_size, size_t *region_starts);

// Creates threads to process each region
// src: Pointer to the memory-mapped file
// region_starts: Array of starting points for each region
// file_size: The size of the file in bytes
// threads: Array of pthread_t to store thread information
// thread_args: Array of region_args_t structs to store region information
void create_threads(char *src, size_t *region_starts, size_t file_size,
                    pthread_t *threads, region_args_t *thread_args);

// Joins threads after they have finished processing
// threads: Array of pthread_t containing thread information
void join_threads(pthread_t *threads);

// Processes a region of the file for run-length encoding
// args: Pointer to the region_args_t struct containing region information
// Returns: A pointer to the region_args_t struct
void *process_region(void *args);

#endif // !MULTI_THREADING_H
