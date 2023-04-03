#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stdout, "wzip: file1 [file2 ...]\n");
    exit(1);
  }

  int counter = 0;
  char prev_char = 0;
  char current_char;

  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == NULL) {
      fprintf(stdout, "Error opening file: %s\n", argv[i]);
      exit(1);
    }

    while (fread(&current_char, sizeof(char), 1, file) == 1) {
      if (current_char != prev_char) {
        if (counter > 0) {
          fwrite(&counter, sizeof(int), 1, stdout);
          fwrite(&prev_char, sizeof(char), 1, stdout);
        }
        counter = 1;
        prev_char = current_char;
      } else {
        counter++;
      }
    }
    fclose(file);
  }

  if (counter > 0) {
    fwrite(&counter, sizeof(int), 1, stdout);
    fwrite(&prev_char, sizeof(char), 1, stdout);
  }

  return 0;
}
