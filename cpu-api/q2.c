#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  if (fd == -1) {
    fprintf(stderr, "open failed\n");
  }
  int rc = fork();
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    const char * child_msg = "Hello, I am child process. Writing on you\n";
    printf("************ Child process writing on file ************\n");
    write(fd, child_msg , strlen(child_msg));
    close(fd);
    exit(0);
  } else {
    // wait(NULL);
    const char * parent_msg = "Hello, I am parent process. Writing on you\n";
    printf("************ Parent process writing on file ************\n");
    write(fd, parent_msg, strlen(parent_msg));
    close(fd);
    exit(0);
  }
  return EXIT_SUCCESS;
}

