#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int rc = fork();
  char *const envp[] = {NULL};
  char *const argv[] = {"ls", NULL};

  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    int wc = wait(NULL); // returns the process ID of the terminated child
    printf("Executing child process, value of wait() = %d\n", wc);
  } else {
    printf("Executing parent process\n");
    sleep(1);
  }
  return EXIT_SUCCESS;
}
