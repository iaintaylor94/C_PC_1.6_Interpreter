#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/errno.h>

// Global variables
FILE *gInterpreterFile;

const unsigned int gkMemSize = 1000;

const unsigned int kNumberRegisters = 10;
unsigned int registers [10];

const unsigned int kNumberRAM = 1000;
unsigned int RAM [kNumberRAM];

unsigned int gInstructionPointer = 0;

unsigned int gNumInstructions = 0; // 0/1 ????

// Declare Functions
void usage (char *);
int reset (void);

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
  int nCases;
  nCases  = fgetc(gInterpreterFile);
  while (fgetc(gInterpreterFile) != '\n'); // End of Line
  fgetc(gInterpreterFile); // Blank space between number of cases and the instructions

  for (int i = 0; i < nCases; i++) {
    if(reset() != 0) {
      fprintf (stderr, "Error: Failed to reset the interpreter.\n");
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
  memset(registers, 0, sizeof(registers)); // Reset registers
  memset(RAM, 0, sizeof(RAM)); //Reset RAM
  gInstructionPointer = 0; // Reset instruction pointer
  gNumInstructions = 0; // Reset instruction counter 0/1 ???
  return (0);
}