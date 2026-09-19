#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  printf("hello world (pid:%d)\n", (int) getpid());
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    printf("Value of x before modification in child process: %d\n", x);
    x = 200;
    printf("hello, I am child (pid:%d)\n", (int) getpid());
    printf("Value of x after modification in child process: %d\n", x);
    sleep(1);
  } else {
    // parent goes down this path (original process)
    int wc = wait(NULL); // returns the process ID of the terminated child
    printf("Value of x before modification in parent process: %d\n", x);
    x = 300;
    printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int) getpid());
    printf("Value of x after modification in parent process: %d\n", x);
  }
  return EXIT_SUCCESS;
}
