#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ITERATIONS 100000
#define BILLION 1000000000LL

int main()
{
  struct timespec start, end;
  long long sum = 0;
  double avg;
  char buffer[1];

  for(int i = 0; i < ITERATIONS; i++) {
    if (clock_gettime(CLOCK_BOOTTIME, &start) < 0) {
      perror("clock_gettime");
      exit(EXIT_FAILURE);
    }

    /* if(execl("/bin/ls", "ls", NULL) < 0) {
      perror("execl");
      exit(EXIT_FAILURE);
    } */

    if(read(STDIN_FILENO, buffer, 0) < 0) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    if (clock_gettime(CLOCK_BOOTTIME, &end) < 0) {
      perror("clock_gettime");
      exit(EXIT_FAILURE);
    }

    long long elapsed_ns = (end.tv_sec - start.tv_sec) * BILLION + (end.tv_nsec - start.tv_nsec);
    sum += elapsed_ns;
  }
  
  avg = sum / (float)ITERATIONS;

  printf("Total time: %lld ns\n", sum);
  printf("Average execl(): %.2f ns\n", avg);

  return 0;
}
