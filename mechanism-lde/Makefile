CFLAGS=-g

all: syscall_measurement

clean:
	rm -f syscall_measurement.out

syscall_measurement: syscall_measurement.c
	gcc -o syscall_measurement.out syscall_measurement.c $(CFLAGS) 

