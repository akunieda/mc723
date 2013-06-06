#include <stdio.h>

int main(int argc, char *argv[]){
  volatile int* lock = (volatile int*) 0xFFFFFFFF;
  while (*lock);

  int i;
  for(i=0;i<10;i++)
    printf("Hi from processor MIPS!\n");

  *lock = 0;

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

