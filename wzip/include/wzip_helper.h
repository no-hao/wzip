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

void process_file(const char *filename, int *counter, char *prev_char);

#endif // !WZIP_HELPER_H
