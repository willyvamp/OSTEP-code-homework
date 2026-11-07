# Chapter 13

## Question 2

### Now, run free, perhaps using some of the arguments that might be useful (e.g., -m, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

My Arch Linux machine:
               total        used        free      shared  buff/cache   available
Mem:            7783        4338         880        1337        3577        3445
Swap:           4095         819        3276

Estimated memory available for new applications is shown in *available*

## Question 3

### Next, create a little program that uses a certain amount of memory, called memory-user.c. This program should take one command line argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.

Normally, malloc() allocates memory from the heap, and adjusts the size of the heap as required, using sbrk(2). When allocating blocks of memory larger than MMAP_THRESHOLD bytes, the glibc malloc() implementation allocates the memory as a private  anonymous  mapping  using mmap(2). MMAP_THRESHOLD is 128 kB by default, but is adjustable using mallopt(3).

*malloc()* alone does not necessarily cause physical memory to be allocated immediately. By accessing every byte, your program forces the OS to handle the corresponding virtual memory pages. This is an example of **demand paging**.

## Question 4

### Now, while running your memory-user program, also (in a different terminal window, but on the same machine) run the free tool. How do the memory usage totals change when your program is running? How about when you kill the memory-user program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?

*watch -n 1 free -h*
this command show the memory usage updates every 1 second. 

The *available* memory is decreased an amount same as the input from command line after the program is executed and reset the previous value right after the program is killed.

## Question 5
### Let’s try one more tool, known as pmap. Spend some time, and read the pmap manual page in detail.

The **pmap** reports the memory map of a process or processes

*pmap - [option ...] pid ...*

## Question 6
### To use pmap, you have to know the process ID of the process you’re interested in. Thus, first run ps auxw to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your memory-user program in this case (indeed, you can even have that program call getpid() and print out its PID for your convenience).

**Output of program after using getpid() syscall**

❯ ./memory-user.out 100
Malloc PID: 721532
Allocated 104857600 bytes of memory

## Question 7
### Now run pmap on some of these processes, using various flags (like -X) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?

**Output of program after using *pmap -X 721532* command**

❯ pmap -X 721532
    562e915d8000 rw-p 00000000  00:00        0    132      4      4         4          4         4   0        0              0             0              0               0    0       0      0           0 [heap]
    7fde70bff000 rw-p 00000000  00:00        0 102404 102404 102404    102404     102404    102404   0        0              0             0              0               0    0       0      0           1 

The [heap] mapping is only 132 KB even though 100 MB is allocated by memory-user program, because:

Linux's memory allocator (malloc() in glibc) can obtain memory from two main sources:

1. brk() / sbrk(): Expands the traditional process heap.

2. mmap(): Creates a separate anonymous memory mapping.

For sufficiently large allocations, glibc commonly uses mmap() instead of expanding the traditional heap.

100 MB allocation is large enough that glibc uses a separate anonymous mapping.


The following is the C standard library loaded into your process. It provides functions such as: malloc(), printf(), fprintf(), atoi(). The library is mapped into your virtual address space. Some of its pages can be shared with other processes.

7fde77000000 r--p ... libc.so.6
7fde77024000 r-xp ... libc.so.6
7fde7719f000 r--p ... libc.so.6
7fde77215000 r--p ... libc.so.6
7fde77219000 rw-p ... libc.so.6

## Question 8
### Finally, let’s run pmap on your memory-user program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?

The key distinction:
- Size tells you how much virtual address space is mapped.
- RSS tells you how much of that mapping is currently resident in physical memory.
- PSS accounts for shared physical pages proportionally.

