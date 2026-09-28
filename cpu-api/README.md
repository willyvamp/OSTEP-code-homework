# Chapter 5

## Question 1

### Write a program that calls fork(). Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?

The value of the variable in the child process can be changed if a new value is assigned to a variable in the child process. When both the child and parent change the value of x, each process maintain their own copy of varibles. Because child and parent process have their own private address space exclusive of each other. Both process (child and parent) can't interfare in each other's address space (memory).

## Question 2

### Write a program that opens a file (with the open() system call) and then calls fork() to create a new process. Can both the child and parent access the file descriptor returned by open()? What happens when they are writing to the file concurrently, i.e., at the same time?

Both the child and parent can access the file descriptor returned by open(). Both are able to write to the file but it's *non-determinism* if wait() is not called in the parent process.

## Question 3

### Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling wait() in the parent?

When fork() succeeds, there are two independent processes: parent and child. Both processes continue executing from the instruction after *fork()*.

**They can run concurrently**

The operating system scheduler decides when each process gets CPU time.

**On a single CPU core, they aren't literally executing at exactly the same instant**

If your computer has one CPU core, only one process can execute an instruction at a time.

The scheduler rapidly switches between them. This gives you concurrency, but not true simultaneous execution.

**On multiple CPU cores, they can actually execute simultaneously**

Suppose your CPU has multiple cores:

Then the parent and child can genuinely execute at the same time. That is parallel execution.

**The *fork()* call creates the two processes, but it doesn't establish an execution order between them**

This is why synchronization is necessary.

We can use *wait()* for synchronization. However, it's not only the solution. We can use *pause()* and Signal handler for synchronization.

## Question 4

### Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?

**RTFM for details**
```c
#include <unistd.h>

int execl(const char *filepath, const char* arg1, const char* arg2,...)
int execlp(const char *filename, const char* arg1, const char* arg2,...)
int execle(const char *filepath, const char* arg1, const char* arg2,..., char* const envp[])
int execv(const char* filepath, char*argv[])
int execvp(const char* filename, char *argv[])
int execve(const char* filepath, char* argv[], char* const envp[])
```

## Question 5

### Now write a program that uses wait() to wait for the child process to finish in the parent. What does wait() return? What happens if you use wait() in the child?

*wait()*: on success, returns the process ID of the terminated child; on error, -1 is returned.

If we use *wait()* in child process then wait() returns -1. Because, there is no child of child. So, there is no wait for any process (child process) to exit.

## Question 6

### Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be useful?

*waitpid()* is used when we want to wait or a specific child process rather than aiting for all child processes to exit.It also allow us to specify more behaviors

## Question 7

### Write a program that creates a child process, and then in the child closes standard output (STDOUT FILENO). What happens if the child calls printf() to print some output after closing the descriptor?

If we close stdout file descriptor we can't be able to write something on the screen using printf(). However, no error would occurred.

## Question 8

### Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
