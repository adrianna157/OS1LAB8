CC = gcc 
CFLAGS = -g -ggdb -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
PROG1 = matrix_mult_MP 
PROG2 = primtMT


DEFINES = DTEST_MODE

all: $(PROG1) $(PROG2) 

matrix_mult_MP: matrix_mult_MP.o
	$(CC) $(CFLAGS) -o matrix_mult_mp.c

fifo_server.o: matrix_mult_MP.c  
	$(CC) $(CFLAGS) -c matrix_mult_MP.c 	 

primMT: primtMT.o
	$(CC) $(CFLAGS) -o primtMT primtMT.o 


fifo_client.o: primtMT.c  
	$(CC) $(CFLAGS) -c  fifo_client.c  

clean:
	rm -f $(PROG) $(PROG2) *.o *.gch 