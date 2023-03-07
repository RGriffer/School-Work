programs = Initiator.c Pell.c Composite.c Total.c
CFLAGS = -std=c11 -Wall

build: 
	gcc -lrt -o Initiator Initiator.c
	gcc -lrt -o Pell Pell.c
	gcc -lrt -o Composite Composite.c
	gcc -lrt -o Total Total.c
	gcc -lrt -o Reader Reader.c

clean: 
	-rm Initiator 
	-rm Composite
	-rm Pell
	-rm Total
	-rm Reader
