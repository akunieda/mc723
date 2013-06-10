#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NITER = 1024;
volatile int hit = 0;
volatile int total = 0;

int main(int argc, char *argv[]){
  int i;
  float x, y;
  int local_hit = 0;

  volatile float* random = (volatile float*) 0xFFFFFFFE;
  for(i=0;i<NITER;i++) {
    x = *random;
    y = *random;
    if (x*x + y*y <= 1.f) local_hit++;
  }

  volatile int* lock = (volatile int*) 0xFFFFFFFF;
  while (*lock);
  hit += local_hit;
  total += NITER;
  printf("4 * %d/%d = %lf\n", hit, total, ((double) 4*hit) / ((double) total));
  *lock = 0;

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

