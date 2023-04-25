// rle.h
#ifndef RLE_H
#define RLE_H

#include "wzip_helper.h"
#include <stddef.h>

// Encodes the input string using run-length encoding (RLE) algorithm
run_t *run_length_encode(const char *src, size_t start, size_t end,
                         int *run_count);

// Updates the RLE counter and previous character based on the current run
void update_counter_and_prev_char(run_t current_run, int *counter,
                                  char *prev_char, buffered_output_t *output);

#endif
