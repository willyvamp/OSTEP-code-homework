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
    printf("Executing child process\n");
    // child (new process)
    /* Uncomment only one of these calls */

    // execl("/bin/ls", "ls", NULL);

    // execle("/bin/ls", "ls", NULL, envp);
    
    // execlp("ls", "ls", NULL);

    // execv("/bin/ls", argv);

    execvp("ls", argv);

    // execvpe("/bin/ls", argv, envp);
    
    printf("\n");
    sleep(1);
  } else {
    // parent goes down this path (original process)
    int wc = wait(NULL); // returns the process ID of the terminated child
    printf("hello, I am parent");
  }
  return EXIT_SUCCESS;
}
