#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MB (1 << 20) // 1 x 2^20 = 1048576 = 1024 x 1024

typedef unsigned char byte; // 1 byte

int main(int argc, char *argv[])
{
  if (argc != 2) {
    fprintf(stderr, "error: command line synstax (%s <memory_in_MB>)\n", argv[1]);
    return 1;
  }

  // convert a string from command line to an integer
  int memorysize = atoi(argv[1]);

  if (memorysize <= 0) {
    fprintf(stderr, "error: memory size must be greater than 0\n");
    return 1;
  }

  int memory_in_bytes = memorysize * MB;
  pid_t my_pid = getpid();

  // type casting to byte from int to avoid Segmentation fault
  byte *allocmem = (byte*) malloc(memory_in_bytes);

  printf("Malloc PID: %d\n", my_pid);
  printf("Allocated %d bytes of memory\n", memory_in_bytes);

  int i;

  while(1)
    for(i = 0; i < memory_in_bytes; i++)
      allocmem[i] += 1; 

  free(allocmem);

  return EXIT_SUCCESS;
}
