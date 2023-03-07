README
======

This package includes the following files.

|-- Invoker.java [This is the driver program which will be used to create an instance of the Circular buffer, and create and wait for one thread of producer and one or more threads of and consumer.] (Skeleton Code provided)
|-- Producer.java [Each instance of a producer generates a single number between 0 and 99 (both inclusive) randomly and inserts into the buffer, and reports the location and the time the number was inserted into the buffer] (Skeleton Code provided)
|-- Consumer.java [Each instance of a consumer reads a number from the buffer and reports the location and the time the number was read from the buffer.]
|-- Bdbuffer.java [Creates a circular buffer whose size is passed as an argument to it.]
|-- Makefile [For compiling, and cleaning]
|-- README.txt [This file]

STUDENT NOTES:
I have tried to fix the issue with things printing out of order however it is too late to get help from a TA
Unfortunately have not figured out the fix to get things to print IN ORDER but I'm pretty sure I have all of the correct lines, just out of order.
I would appreciate it if you (the grader) would be willing to look in the code and see if there is a way to fix it, if you don't have time I completely understand


Questions:

1. The problem of producer consumer is solved using _____mutex locks_____. - 1 point
	a. Mutex Locks
	b. Semaphores

2. What two functions defined in Java are used for synchronization between producer and consumers in your program? _____wait()_____ and ____notify()______. - 2 points

3. In which function do you override the body to define the new body of a thread in java? __________. - 1 point

4. Which function is used to wait for a thread to finish and come back to calling program i.e. for a thread to die? ______join()____. - 1 point

NOTE:

Lab systems by default use Java 11 which supports nanosecond timestamp. If after logging in and running 'java -version', it doesn't output version 11, use the following two commands:

	$ export PATH=/usr/lib/jvm/jre-11-openjdk/bin/:$PATH

	$ export LD_LIBRARY_PATH=/usr/lib/jvm/jre-11-openjdk/lib/:$LD_LIBRARY_PATH


