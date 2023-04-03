// wzip source code here.
#include <stdio.h>

int main(int argc, char *argv[]) {
  // Parse command-line arguments
  if (argc < 2) {
    fprintf(stderr, "wzip: file1 [file2 ...]\n");
    return 1;
  }

  // Initialize variables
  int counter = 0;
  int curr_char, prev_char;

  // Loop through input files
  for (int i = 1; i < argc; ++i) {
    char *input_file = argv[i];

    // printf("Processing file: %s\n", input_file);

    // Open input file
    FILE *curr_file = fopen(input_file, "r");

    // Initialize the prev_char with the first character from the input file.
    prev_char = fgetc(curr_file);
    counter = 1;

    // Read input file and perform run-length encoding
    while ((curr_char = fgetc(curr_file)) != EOF) {
      if (curr_char == prev_char) {
        // Characters are the same, increment the counter.
        counter++;
      } else {
        // Compare characters and update counter or write to stdout
        fwrite(&counter, sizeof(int), 1, stdout);
        fwrite(&prev_char, sizeof(char), 1, stdout);

        // Reset the counter and update the previous character.
        counter = 1;
        prev_char = curr_char;
      }
    }

    // Handle the last run-length
    fwrite(&counter, sizeof(int), 1, stdout);
    fwrite(&prev_char, sizeof(char), 1, stdout);

    // Close input file
    fclose(curr_file);
  }

  // Exit with return code 0
  return 0;
}
