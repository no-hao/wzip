#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include "../include/wzip_helper.h"

void adjust_region_starts(char *src, size_t file_size, size_t *region_starts);

void *process_region(void *args);

void create_threads(char *src, size_t *region_starts, size_t file_size,
                    pthread_t *threads, region_args_t *thread_args);

void join_threads(pthread_t *threads);

#endif // !MULTI_THREADING_H
