#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define ITERATIONS 100000
#define BILLION 1000000000LL

int main(void)
{
  struct timespec start, end;
  double avg;
  char buffer[1];

  clock_gettime(CLOCK_MONOTONIC, &start);

  for(long i = 0; i < ITERATIONS; i++) {
    // just measures operation of read() syscall
    read(STDIN_FILENO, buffer, 0);
  }

  clock_gettime(CLOCK_MONOTONIC, &end);

  long long elapsed_ns = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
  
  avg = (double)elapsed_ns / ITERATIONS;

  printf("Total time: %lld ns\n", elapsed_ns);
  printf("Average read(): %.2f ns\n", avg);

  return 0;
}
