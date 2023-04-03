#include "../include/wzip_helper.h"
#include <stdio.h>
#include <stdlib.h>

// processes a file and update the counter and prev_car variables.
void process_file(const char *filename, int *counter, char *prev_char) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stdout, "Error opening file: %s\n", filename);
    exit(1);
  }

  char curr_char;
  // Read the file character by character.
  while (fread(&curr_char, sizeof(char), 1, file) == 1) {
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
  fclose(file);
}
