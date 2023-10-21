#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/errno.h>

// Declare Functions
void usage (char *);

int main(int argc, char *argv[]) {

  // File Initialization
  FILE *gInterpreterFile;
  
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInterpreterFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }





  
  // File Close
  fclose (gInterpreterFile);
  
  return 0;
}


// Define Functions
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}