#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NITER = 1024;
const float R = 0.5f;

int main(int argc, char *argv[]){
  int i;
  float x, y;
  int hit = 0;

  volatile float* random = (volatile float*) 0xFFFFFFFE;
  for(i=0;i<NITER;i++) {
    x = *random - R;
    y = *random - R;
    if (x*x + y*y <= R*R) hit++;
  }

  volatile int* lock = (volatile int*) 0xFFFFFFFF;
  while (*lock);
  printf("4 * %d/%d = %lf\n", hit, NITER, ((double) 4*hit) / ((double) NITER));
  *lock = 0;

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

