#include "../include/wzip_helper.h"
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define THRESHOLD 4096

size_t get_file_size(int fd) {
  struct stat st;
  if (fstat(fd, &st) == -1) {
    perror("fstat");
    exit(EXIT_FAILURE);
  }
  return st.st_size;
}

void *process_region(void *args) {
  region_args_t *region_args = (region_args_t *)args;
  char *src = region_args->src;
  size_t start = region_args->start;
  size_t end = region_args->end;
  run_t *shared_buffer = region_args->shared_buffer;

  // Initialize run-length encoding variables
  run_t current_run = {1, src[start]};
  int run_count = 0;

  // Calculate the allocated size of the shared buffer for this region
  size_t shared_buffer_size =
      (region_args->end - region_args->start) * sizeof(run_t);

  // Perform run-length encoding for the region
  for (size_t i = start + 1; i < end; i++) {
    if (src[i] == current_run.character) {
      current_run.count++;
    } else {
      if (run_count * sizeof(run_t) >= shared_buffer_size) {
        fprintf(stderr, "Shared buffer overflow in process_region()\n");
        exit(EXIT_FAILURE);
      }
      shared_buffer[run_count++] = current_run;
      current_run.character = src[i];
      current_run.count = 1;
    }
  }
  if (run_count * sizeof(run_t) >= shared_buffer_size) {
    fprintf(stderr, "Shared buffer overflow in process_region()\n");
    exit(EXIT_FAILURE);
  }
  shared_buffer[run_count++] = current_run;

  // Store the encoded run_count in the region_args structure
  region_args->run_count = run_count;

  return (void *)region_args;
}

void process_multi_threaded(char *src, size_t file_size, int *counter,
                            char *prev_char) {
  size_t region_starts[3];
  region_starts[0] = 0;
  region_starts[1] = file_size / 3;
  region_starts[2] = 2 * file_size / 3;

  // Find the boundaries of runs
  for (int i = 1; i < 3; i++) {
    while (region_starts[i] < file_size &&
           src[region_starts[i]] == src[region_starts[i] - 1]) {
      region_starts[i]++;
    }
  }

  pthread_t threads[3];
  region_args_t thread_args[3];
  run_t *shared_buffer = malloc(file_size * sizeof(run_t));

  for (int i = 0; i < 3; i++) {
    thread_args[i].src = src;
    thread_args[i].start = region_starts[i];
    thread_args[i].end = (i == 2) ? file_size : region_starts[i + 1];
    thread_args[i].shared_buffer =
        shared_buffer +
        (file_size / 3) *
            i; // Allocate separate memory segments for each thread

    if (pthread_create(&threads[i], NULL, process_region, &thread_args[i]) !=
        0) {
      perror("pthread_create");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < 3; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  // Output the results directly from the shared buffer
  for (int i = 0; i < 3; i++) {
    region_args_t *current_args = &thread_args[i];
    for (int j = 0; j < current_args->run_count; j++) {
      run_t current_run = current_args->shared_buffer[j];
      if (current_run.character == *prev_char) {
        *counter += current_run.count;
      } else {
        if (*counter > 0) {
          fwrite(counter, sizeof(int), 1, stdout);
          fwrite(prev_char, sizeof(char), 1, stdout);
        }
        *counter = current_run.count;
        *prev_char = current_run.character;
      }
    }
  }

  // Free memory
  free(shared_buffer);
}

void process_file(const char *filename, int *counter, char *prev_char) {
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  size_t file_size = get_file_size(fd);

  if (file_size <= THRESHOLD) {
    // Process the file using the existing single-threaded approach
    process_single_threaded(fd, counter, prev_char);
  } else {
    // Process the file using multi-threaded approach with mmap
    char *src = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (src == MAP_FAILED) {
      perror("mmap");
      exit(EXIT_FAILURE);
    }

    process_multi_threaded(src, file_size, counter, prev_char);

    if (munmap(src, file_size) == -1) {
      perror("munmap");
      exit(EXIT_FAILURE);
    }
  }

  if (close(fd) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  }
}

void process_single_threaded(int fd, int *counter, char *prev_char) {
  char curr_char;
  // Read the file character by character.
  while (read(fd, &curr_char, sizeof(char)) == 1) {
    // If the current char is diff from the prev one, write the count and char
    if (curr_char != *prev_char) {
      if (*counter > 0) {
        fwrite(counter, sizeof(int), 1, stdout);
        fwrite(prev_char, sizeof(char), 1, stdout);
      }
      *counter = 1;
      *prev_char = curr_char;
    } else {
      (*counter)++;
    }
  }
}
