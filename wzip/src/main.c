#include "../include/output_buffer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // check for the correct num of arguments.
  if (argc < 2) {
    fprintf(stdout, "wzip: file1 [file2 ...]\n");
    exit(1);
  }

  int counter = 0;
  char prev_char = 0;

  for (int i = 1; i < argc; i++) {
    process_and_compress_file(argv[1], &counter, &prev_char);
  }

  if (counter > 0) {
    fwrite(&counter, sizeof(int), 1, stdout);
    fwrite(&prev_char, sizeof(char), 1, stdout);
  }

  return 0;
}
