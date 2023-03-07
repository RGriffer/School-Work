README
======

A. This package includes the following files. In your own readme file, modify the information as needed.

|-- Description PDF of the assignment
|-- README.txt [This file]


B. Use your designed makefile 
To compile the code and build the executable using the command 

systemprompt>  make

To remove the  executable files use

systemprompt>  make clean

To run the program use (assuming seed is 3) 

systemprompt> ./Initiator 3

which will run the program and generate the outputs.


C. Answer the following questions (1 point each, select/type the right answer).

  1. What is the main difference between Malloc() and Calloc()?
          The main difference between Malloc() and Calloc() is the amount of arguments they take.
          Malloc() takes a single argument while Calloc() takes 2. 
          Malloc() also does not initialize the memory that it is calling while Calloc() initializes the memory that it is calling to 0.
  
  2. When dynamically allocating an integer array, Malloc takes the number of elements as the input? –  
          False: It takes the size of the int on the machine in bytes and multiplies it by the number of elements desired as input.
          So in a way it does take the number of elements but that is not all that it takes as the input. Therefore False.
          
  3. What happens if memory is not properly freed after using dynamic memory allocation?
          It causes a memory leak.
          Unfreed memory can build up over time in larger files and cause machine slowdown and crashes due to the unfreed memory trying to be allocated,
          but there simply isn't enough to go around. This is a memory leak.
          
  4. What is the purpose of the headerfile Worker.h and Why is Initiator.h not necessary?
          Worker.h is necessary because we need to be able to call the methods of Worker inside Initiator
          and since our methods are being called from Initiator.c, Worker needs the header file to pull the data for the methods.
          Initiator does not need one due to us not needing to call Initiator methods in other files.
          
  5. Describe the * and & operators in the context of pointers and references?
          * is a pointer: A pointer is a variable that holds memory address of another variable. A pointer needs to be dereferenced with * operator to access the memory location it points to. 
          & is a reference: A reference variable is an alias, that is, another name for an already existing variable. A reference, like a pointer, is also implemented by storing the address of an object. 
          A reference can be thought of as a constant pointer.
  


VALGRIND OUTPUTS HERE:

NO LEAK:

[Initiator]: With seed: 7
[Worker]: Number of iterations is: 77
--2097309-- REDIR: 0x4ec80e0 (libc.so.6:free) redirected to 0x4c3609a (free)
[Worker]: Iteration with maximum fully divisible elements is 59
--2097309-- REDIR: 0x4edbd60 (libc.so.6:__strlen_sse2) redirected to 0x4c38380 (__strlen_sse2)
[Initiator]: Running ratio: 0.122461
==2097309==
==2097309== HEAP SUMMARY:
==2097309==     in use at exit: 0 bytes in 0 blocks
==2097309==   total heap usage: 78 allocs, 78 frees, 38,872 bytes allocated
==2097309==
==2097309== All heap blocks were freed -- no leaks are possible
==2097309==
==2097309== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
cheyenne:~/cs370/HW1$ 


WITH LEAK:
[Initiator]: With seed: 7
[Worker]: Number of iterations is: 77
[Worker]: Iteration with maximum fully divisible elements is 59
--2097658-- REDIR: 0x4edbd60 (libc.so.6:__strlen_sse2) redirected to 0x4c38380 (__strlen_sse2)
[Initiator]: Running ratio: 0.122461
--2097658-- REDIR: 0x4ec80e0 (libc.so.6:free) redirected to 0x4c3609a (free)
==2097658==
==2097658== HEAP SUMMARY:
==2097658==     in use at exit: 37,848 bytes in 77 blocks
==2097658==   total heap usage: 78 allocs, 1 frees, 38,872 bytes allocated
==2097658==
==2097658== Searching for pointers to 77 not-freed blocks
==2097658== Checked 71,600 bytes
==2097658==
==2097658== 37,848 bytes in 77 blocks are definitely lost in loss record 1 of 1
==2097658==    at 0x4C34F0B: malloc (vg_replace_malloc.c:307)
==2097658==    by 0x4007F0: get_running_ratio (in /s/bach/c/under/rgriffer/cs370/HW1/Initiator)
==2097658==    by 0x400759: main (in /s/bach/c/under/rgriffer/cs370/HW1/Initiator)
==2097658==
==2097658== LEAK SUMMARY:
==2097658==    definitely lost: 37,848 bytes in 77 blocks
==2097658==    indirectly lost: 0 bytes in 0 blocks
==2097658==      possibly lost: 0 bytes in 0 blocks
==2097658==    still reachable: 0 bytes in 0 blocks
==2097658==         suppressed: 0 bytes in 0 blocks
==2097658==
==2097658== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
cheyenne:~/cs370/HW1$
