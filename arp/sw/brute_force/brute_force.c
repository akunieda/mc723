#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAXKEY = 10000;
volatile int found = 0;

int main(int argc, char *argv[]){
  int i;
  int nproc = atoi(argv[1]), tproc = atoi(argv[2]);
  int l = (MAXKEY / tproc) * nproc, r = l + (MAXKEY / tproc);
  volatile int* lock = (volatile int*) 0xFFFFFFFF;

  /* while (*lock); */
  /* printf("> nproc = %d\n", nproc); */
  /* printf("l = %d, r = %d\n", l, r); */
  /* *lock = 0; */

  volatile char* check = (volatile char*) (0xFFFFFFFD - MAXKEY);
  for(i=l; i<r && !found; i++)
    if(check[i]) {
      printf("The key is %d\n", i);
      found = 1;
    }

  while (*lock);
  printf("%d/%d\n", i-l, r-l);
  *lock = 0;

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

