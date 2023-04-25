#include "../include/wzip_helper.h"
#include "../include/file_io.h"
#include "../include/multi_threading.h"
#include "../include/output_buffer.h"
#include "../include/rle.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 4096

// Frees memory allocated for thread arguments
void free_memory(region_args_t *thread_args) {
  for (int i = 0; i < 3; i++) {
    free(thread_args[i].shared_buffer);
  }
}

// Outputs results for single-threaded processing
void output_results_single_threaded(run_t *encoded_runs, int run_count,
                                    int *counter, char *prev_char,
                                    buffered_output_t *output) {
  // Output the results directly from the encoded_runs
  for (int i = 0; i < run_count; i++) {
    run_t current_run = encoded_runs[i];
    update_counter_and_prev_char(current_run, counter, prev_char, output);
  }
  buffered_output_flush(output);
}

// Processes and compresses a file
void process_and_compress_file(const char *filename, int *counter,
                               char *prev_char) {
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  size_t file_size = get_file_size(fd);

  char *src = mmap_file(fd, file_size);

  if (file_size <= THRESHOLD) {
    process_single_threaded(src, file_size, counter, prev_char);
  } else {
    process_multi_threaded(src, file_size, counter, prev_char);
  }

  unmap_file(src, file_size);

  close_file(fd);
}

// Processes input data in multi-threaded mode
void process_multi_threaded(char *src, size_t file_size, int *counter,
                            char *prev_char) {
  size_t region_starts[3];
  region_starts[0] = 0;
  region_starts[1] = file_size / 3;
  region_starts[2] = 2 * file_size / 3;

  adjust_region_starts(src, file_size, region_starts);

  pthread_t threads[3];
  region_args_t thread_args[3];

  create_threads(src, region_starts, file_size, threads, thread_args);

  join_threads(threads);

  buffered_output_t output;
  buffered_output_init(&output, 4096);
  output_results(thread_args, counter, prev_char, &output);
  buffered_output_free(&output);

  free_memory(thread_args);
}

// Processes input data in single-threaded mode
void process_single_threaded(char *src, size_t file_size, int *counter,
                             char *prev_char) {
  int run_count;
  run_t *encoded_runs = run_length_encode(src, 0, file_size, &run_count);

  buffered_output_t output;
  buffered_output_init(&output, 4096);
  output_results_single_threaded(encoded_runs, run_count, counter, prev_char,
                                 &output);
  buffered_output_free(&output);

  // Free memory
  free(encoded_runs);
}

// Outputs results for multi-threaded processing
void output_results(region_args_t *thread_args, int *counter, char *prev_char,
                    buffered_output_t *output) {
  // Output the results directly from the shared buffer
  for (int i = 0; i < 3; i++) {
    region_args_t *current_args = &thread_args[i];
    for (int j = 0; j < current_args->run_count; j++) {
      run_t current_run = current_args->shared_buffer[j];
      update_counter_and_prev_char(current_run, counter, prev_char, output);
    }
  }
  buffered_output_flush(output);
}
