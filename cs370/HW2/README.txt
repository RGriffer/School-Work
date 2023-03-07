Threading practice

1. What is the return value for the fork() in a child process?
    Upon successful completion, fork() returns 0 to the child process and returns the process ID of the child process to the parent process.
    So it returns 0 in the child process.

2. Give a reason for the fork() to fail?
    System-imposed limit on total number of processes under execution would be exceeded.
    Lack of memory to allocate to new thread.

3. How many of the least significant bits of the status does WEXITSTATUS return?
    The least significant 8 bits.

4. Which header file has to be included to use the WEXITSTATUS
    <sys/wait.h>

5. In this program, are we doing a sequential processing or a concurrent processing with respect to
the child processes? Sequential processing is when only one of the child processes is running at one time, 
and concurrent processing is when more than one child process can be running at the same time.
    In this one we are doing sequential because when using wait(), we tell the parent to wait for the child before continuing 
    onto the next child to process.

6. Is it possible to have any anomalies in the output from child process and the output from parent
process. Provide a reason for that possible situation. (2 points )
    A possible reason for anomalies in outputs could be from the I/O buffers not being flushed before forking,
    The next time that each of them does something to flush its buffer (such as printing a newline in the case of terminal output)
    you will see that buffered output in addition to any new output produced by that process.
    
    
Contained in the tar file are 6 files, Total.c, Pell.c, Composite.c, Initiator.c, Makefile, and this README.txt file.
make build will create all of the executables, 
make clean will get rid of them.
all questions and answers contained above.
