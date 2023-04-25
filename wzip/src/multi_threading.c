#include "../include/multi_threading.h"
#include "../include/rle.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void adjust_region_starts(char *src, size_t file_size, size_t *region_starts) {
  for (int i = 1; i < 3; i++) {
    while (region_starts[i] < file_size &&
           src[region_starts[i]] == src[region_starts[i] - 1]) {
      region_starts[i]++;
    }
  }
}

void create_threads(char *src, size_t *region_starts, size_t file_size,
                    pthread_t *threads, region_args_t *thread_args) {
  for (int i = 0; i < 3; i++) {
    thread_args[i].src = src;
    thread_args[i].start = region_starts[i];
    thread_args[i].end = (i == 2) ? file_size : region_starts[i + 1];

    if (pthread_create(&threads[i], NULL, process_region, &thread_args[i]) !=
        0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }
}

void join_threads(pthread_t *threads) {
  for (int i = 0; i < 3; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }
}

void *process_region(void *args) {
  region_args_t *region_args = (region_args_t *)args;
  char *src = region_args->src;
  size_t start = region_args->start;
  size_t end = region_args->end;

  region_args->shared_buffer =
      run_length_encode(src, start, end, &region_args->run_count);

  return (void *)region_args;
}
