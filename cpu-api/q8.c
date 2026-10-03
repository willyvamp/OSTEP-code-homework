#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int pfd[2];
  if (pipe(pfd) < 0) {
    fprintf(stderr, "pipe failed\n");
    exit(1);
  }
  int rc1 = fork();
  if (rc1 < 0) {
    //fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc1 == 0) {
      printf("Child proc 1 - ls is executing\n");
      close(pfd[0]); // Only write the pipe to standard output
      dup2(pfd[1], STDOUT_FILENO); // 1 (integer value) - STDOUT_FILENO <unistd.h> - stdout <stdio.h>
      close(pfd[1]); //pfd[1] is no longer needed directly
      if (execl("/bin/ls", "ls", NULL) < 0) {
        fprintf(stderr, "execl failed\n");
        exit(1);
      }
  } else {
    int rc2 = fork();
    if (rc2 < 0) {
      //fork failed; exit
      fprintf(stderr, "fork failed\n");
      exit(1);
    } else if (rc2 == 0) {
      printf("Child proc 2 - wc -l is executing\n");
      close(pfd[1]); // Only read the pipe from standard input
      dup2(pfd[0], STDIN_FILENO); // 0 (integer value) - STDIN_FILENO <unistd.h> - stdin <stdio.h>
      close(pfd[0]); //pfd[0] is no longer needed directly
      if (execl("/bin/wc", "wc", "-l", NULL) < 0) {
        fprintf(stderr, "execl failed\n");
        exit(1);
      }
    } else {
      /* Parent proc does not use the pipe. 
      Close two file description because wc needs all write ends of the pipe to be closed before it receives EOF. */
      close(pfd[0]);
      close(pfd[1]);

      waitpid(rc2, NULL, 0);
      sleep(1);
      printf("This is parent process. End of program\n");
    }
  }
  return EXIT_SUCCESS;
}
