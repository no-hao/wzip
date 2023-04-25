#include "../include/output_buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Allocates memory for the output buffer and initializes the structure
void buffered_output_init(buffered_output_t *output, size_t capacity) {
  output->buffer = malloc(capacity);
  output->capacity = capacity;
  output->position = 0;
}

// Writes the content of the output buffer to stdout and resets the position
void buffered_output_flush(buffered_output_t *output) {
  fwrite(output->buffer, 1, output->position, stdout);
  output->position = 0;
}

// Deallocates the memory used for the output buffer
void buffered_output_free(buffered_output_t *output) { free(output->buffer); }

// Appends an RLE-encoded pair (counter and character) to the output buffer
// Flushes the buffer if the new data would exceed the buffer capacity
void buffered_output_write(buffered_output_t *output, int *counter,
                           char *prev_char) {
  if (output->position + sizeof(int) + sizeof(char) > output->capacity) {
    buffered_output_flush(output);
  }

  memcpy(output->buffer + output->position, counter, sizeof(int));
  output->position += sizeof(int);
  memcpy(output->buffer + output->position, prev_char, sizeof(char));
  output->position += sizeof(char);
}
