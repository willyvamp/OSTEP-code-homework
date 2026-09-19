#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
// #include <sys/wait.h> // for wait() system call

// Synchronization of child and parent process using wait() system call
/* int main(int argc, char *argv[])
{
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    printf("hello\n");
    sleep(1);
  } else {
    // parent goes down this path (original process)
    int wc = wait(NULL);
    printf("goodbye\n");
  }
  return EXIT_SUCCESS;
} */

void sig_handler(int signum) {
    printf("goodbye\n");
    exit(0);
}

/* Synchronization by using signal and pause() system call
 * When fork() succeeds, there are two independent processes: child and parent.
 * Both processes continue executing from the instruction after fork()
 */
int main (int argc, char const *argv[]) {
  int parent_pid = getpid();
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  }
  else if (rc == 0) {
    // child process 
    printf("hello\n");
    kill(parent_pid, SIGCONT); // Send SIGCONT to the parent process.
    exit(0);
  } else { 
    // parent goes down this path (original process)
    // https://www.unix.com/302582537-post2.html?s=c29ed69cf8a6adc4c14984b71e3aa176
    /* You can sleep "indefinitely" with the pause() function,
       defined in <unistd.h>, which will sleep until you receive
       a signal.You can wake a thread with pthread_kill() or kill()
       to send some signal that won't kill it (SIGCONT seems appropriate).
    */
    signal(SIGCONT, sig_handler); // install signal handler
    pause();
  }
}
