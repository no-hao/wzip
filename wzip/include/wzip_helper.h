// wzip_helper.h
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
  run_t *shared_buffer;
  int run_count;
} region_args_t;

typedef struct {
  char *buffer;
  size_t capacity;
  size_t position;
} buffered_output_t;

// Function prototypes

void process_single_threaded(char *src, size_t file_size, int *counter,
                             char *prev_char);

void process_multi_threaded(char *src, size_t file_size, int *counter,
                            char *prev_char);

void process_and_compress_file(const char *filename, int *counter,
                               char *prev_char);

void free_memory(region_args_t *thread_args);

void output_results_single_threaded(run_t *encoded_runs, int run_count,
                                    int *counter, char *prev_char,
                                    buffered_output_t *output);

void output_results(region_args_t *thread_args, int *counter, char *prev_char,
                    buffered_output_t *output);

#endif // !WZIP_HELPER_H
