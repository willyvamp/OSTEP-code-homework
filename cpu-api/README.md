# Chapter 5

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
