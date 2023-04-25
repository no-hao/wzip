#ifndef WZIP_HELPER_H
#define WZIP_HELPER_H

#include <stddef.h>
#include <sys/types.h>

typedef struct {
  int count;
  char character;
} run_t;

typedef struct {
  char *src;
  size_t start;
  size_t end;
  run_t *runs;
  int run_count;
} region_args_t;

// Function prototypes
size_t get_file_size(int fd);

void *process_region(void *args);

void merge_runs(region_args_t *args1, region_args_t *args2);

void process_single_threaded(int fd, int *counter, char *prev_char);

void process_multi_threaded(char *src, size_t file_size, int *counter,
                            char *prev_char);

void process_file(const char *filename, int *counter, char *prev_char);

#endif // !WZIP_HELPER_H
