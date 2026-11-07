#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define ITERATIONS 1000000

int main(void)
{
    char buffer[1];
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (long i = 0; i < ITERATIONS; i++) {
        read(STDIN_FILENO, buffer, 0);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    long long elapsed_ns =
        (end.tv_sec - start.tv_sec) * 1000000000LL +
        (end.tv_nsec - start.tv_nsec);

    printf("Total time: %lld ns\n", elapsed_ns);
    printf("Average read(): %.2f ns\n",
           (double)elapsed_ns / ITERATIONS);

    return 0;
}
