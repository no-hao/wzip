// buffer_output.h
#ifndef BUFFER_OUTPUT_H
#define BUFFER_OUTPUT_H

#include "wzip_helper.h"
#include <stddef.h>

void buffered_output_free(buffered_output_t *output);

void buffered_output_write(buffered_output_t *output, int *counter,
                           char *prev_char);

void buffered_output_flush(buffered_output_t *output);

void buffered_output_init(buffered_output_t *output, size_t capacity);

#endif
