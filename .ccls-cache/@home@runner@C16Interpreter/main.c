#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/errno.h>

// Global variables
FILE *gInterpreterFile;

const unsigned int gkMemSize = 1000;

const unsigned int gkNumberRegisters = 10;
unsigned int gRegisters [gkNumberRegisters];

const unsigned int gkNumberRAM = 1000;
unsigned int gRAM [gkNumberRAM];

unsigned int gInstructionPointer = 0;

unsigned int gNumInstructions = 0; // 0/1 ????

// Declare Functions
void usage (char *);
int reset (void);
int fillRAM (void);
int printRAM (void);

int main(int argc, char *argv[]) {

  // File Initialization
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInterpreterFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }

  // Get Number of cases
  int nCases  = fgetc(gInterpreterFile) - '0';
  printf ("Number of cases: %d\n", nCases);
  while (fgetc(gInterpreterFile) != '\n'); // End of Line
  fgetc(gInterpreterFile); // Blank space between number of cases and the instructions

  for (int i = 0; i < nCases; i++) {
    if(reset() != 0) {
      fprintf (stderr, "Error: Failed to reset the interpreter.\n");
    }
    if(fillRAM() != 0) {
      fprintf(stderr, "Error: Failed to fill the RAM.\n");
    }
    if(printRAM() != 0) {
      fprintf(stderr, "Error: Failed to print the RAM.\n");
    }

    
    
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

int reset (void) {
  memset(gRegisters, 0, sizeof(gRegisters)); // Reset registers
  memset(gRAM, 0, sizeof(gRAM)); //Reset RAM
  gInstructionPointer = 0; // Reset instruction pointer
  gNumInstructions = 0; // Reset instruction counter 0/1 ???
  return (0);
}

int fillRAM (void) {
  // Fill RAM with instructions
  for (int i = 0; ; i++) {
    fscanf (gInterpreterFile, "%u", &gRAM[i]); // newline??
    gRAM[i] %= gkMemSize;
    if (gRAM[i] == '\0')
      break;
  }
  return 0;
}

int printRAM (void) {
  printf("PRINT RAM\n");
  for (int i = 0; i < gkNumberRAM && gRAM[i] != 0; i++) {
    printf ("gRam[%3d]: %3u\n", i, gRAM[i]);
  }
  return 0;
}