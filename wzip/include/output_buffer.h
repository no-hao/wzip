// buffer_output.h
#ifndef BUFFER_OUTPUT_H
#define BUFFER_OUTPUT_H

#include "wzip_helper.h"
#include <stddef.h>

// Initializes the buffered output structure with a given capacity
void buffered_output_init(buffered_output_t *output, size_t capacity);

// Flushes the content of the output buffer to stdout
void buffered_output_flush(buffered_output_t *output);

// Frees the memory allocated for the buffered output structure
void buffered_output_free(buffered_output_t *output);

// Writes an RLE-encoded pair (counter and character) to the output buffer
void buffered_output_write(buffered_output_t *output, int *counter,
                           char *prev_char);

#endif
