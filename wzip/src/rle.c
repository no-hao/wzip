#include "../include/output_buffer.h"
#include <stdlib.h>

// Perform RLE on the input string between the specified start and end positions
run_t *run_length_encode(const char *src, size_t start, size_t end,
                         int *run_count) {
  // Initialize run-length encoding variables
  run_t current_run = {1, src[start]};
  *run_count = 0;

  run_t *encoded_runs = malloc((end - start) * sizeof(run_t));

  // Perform run-length encoding for the region
  for (size_t i = start + 1; i < end; i++) {
    if (src[i] == current_run.character) {
      current_run.count++;
    } else {
      encoded_runs[(*run_count)++] = current_run;
      current_run.character = src[i];
      current_run.count = 1;
    }
  }

  encoded_runs[(*run_count)++] = current_run;

  return encoded_runs;
}

// Updates the RLE counter and previous character based on the current run
// Flushes the output buffer if the character changes
void update_counter_and_prev_char(run_t current_run, int *counter,
                                  char *prev_char, buffered_output_t *output) {
  if (current_run.character == *prev_char) {
    *counter += current_run.count;
  } else {
    if (*counter > 0) {
      buffered_output_write(output, counter, prev_char);
    }
    *counter = current_run.count;
    *prev_char = current_run.character;
  }
}
