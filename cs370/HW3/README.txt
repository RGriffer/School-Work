Examples of data transfer through pipes

1. Name the function that is used to create a pipe. (1 points)

    pipe() system call

2. Which ends of the pipe denote the read and the write ends of a pipe? (1 points)

    fd[0] for reading
    fd[1] for writing

3. Name the function used to map files or devices in to memory? (1 point)

    mmap()

4. Name the function used to open a shared memory object? What does it return? (2 points)

    shm_open()
    Upon successful completion, the shm_open() function will return a non-negative integer representing the lowest numbered unused file descriptor. 
    Otherwise, it shall return -1 and set errno to indicate the error.
