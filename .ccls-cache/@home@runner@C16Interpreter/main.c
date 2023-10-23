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

void process0 (int, int);
void process1 (bool*);
void process2 (int, int);
void process3 (int, int);
void process4 (int, int);
void process5 (int, int);
void process6 (int, int);
void process7 (int, int);
void process8 (int, int);
void process9 (int, int);

void processInstruction (int, bool*);

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

    // Process program code
    bool bHalt = false;
    while (!bHalt) {
      processInstruction(gRAM[gInstructionPointer], &bHalt);
    }

    // Print number of instructions
    printf ("Case %d: %d instructions\n", i + 1, gNumInstructions);
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
    fscanf (gInterpreterFile, "%u", &gRAM[i]);
    gRAM[i] %= gkMemSize;
    if (gRAM[i] == '\0')
      break;
  }
  return 0;
}

int printRAM (void) {
  // Print RAM
  printf("PRINT RAM\n");
  for (int i = 0; i < gkNumberRAM && gRAM[i] != 0; i++) {
    printf ("gRam[%3d]: %3u\n", i, gRAM[i]);
  }
  return 0;
}

void process0 (int d, int s) {
  // InstructionPointer = register[d], unless s = 0
  if (gRegisters[s] == 0) {
    gInstructionPointer++;
    gNumInstructions++;
  }
  else {
    gInstructionPointer = gRegisters[d];
    gNumInstructions++;
  }
}

void process1 (bool *bHalt) {
  // Halt
  *bHalt = true;
  gNumInstructions++;
  gInstructionPointer++;
}

void process2 (int d, int n) {
  // Set register[d] to n 0 .. 9
  gRegisters[d] = n;
  gRegisters[d] %= 10; // 0 .. 9
  gNumInstructions++;
  gInstructionPointer++;
}

void process3 (int d, int n) {
  // Add n to register[d]
  gRegisters[d] += n;
  gRegisters[d] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void process4 (int d, int n) {
  // Multiply register[d] by n
  gRegisters[d] *= n;
  gRegisters[d] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void process5 (int d, int s) {
  // Set register[d] to register[s]
  gRegisters[d] = gRegisters[s];
  gRegisters[d] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void process6 (int d, int s) {
  // Add register[s] to register[d]
  gRegisters[d] += gRegisters[s];
  gRegisters[d] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void process7 (int d, int s) {
  // Multiply register[d] by register[s]
  gRegisters[d] *= gRegisters[s];
  gRegisters[d] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void process8 (int d, int a) {
  // Set register[d] to RAM[register[a]]
  gRegisters[d] = gRAM[gRegisters[a]];
  gRegisters[d] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void process9 (int s, int a) {
  // Set RAM[regiser[a]] to register[s]]
  gRAM[gRegisters[a]] = gRegisters[s];
  gRAM[gRegisters[a]] %= gkMemSize;
  gNumInstructions++;
  gInstructionPointer++;
}

void processInstruction (int instruction, bool *bHalt) {

  unsigned int right = instruction % 10; instruction /= 10;
  unsigned int left = instruction % 10; instruction /= 10;
  unsigned int instructionType = instruction;
  
  
  switch (instructionType) {
    case 1: // Halt
      process1 (bHalt);
      break;
    
    case 2: // Set register[left] to right 0 .. 9
      process2(left, right);
      break;
    
    case 3: // Add right to register[left]
      process3(left, right);
      break;
    case 4: // Multiply register[left] by right
      process4(left, right);
      break;
    
    case 5: // Set register[left] to register[right]
      process5(left, right);
      break;
    case 6: // Add register[right] to register[left]
      process6(left, right);
      break;
    case 7: // Multiply register[left] by register[right]
      process7(left, right);
      break;
    
    case 8: // Set register[left] to RAM[register[right]]
      process8(left, right);
      break;
    case 9: // Set RAM[regiser[right]] to register[left]]
      process9(left, right);
      break;
    
    case 0: // InstructionPointer = register[left], unless right = 0
      process0(left, right);
      break;
    
    default:
      fprintf (stderr, "Unknown instruction type %d\n", instructionType);
      break;
  }
}