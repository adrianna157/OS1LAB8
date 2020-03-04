CC = gcc 
CFLAGS = -g -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra
PROG1 = matrix_mult_MP
# PROG2 = primtMT


# DEFINES = DTEST_MODE

all: $(PROG1) 
# $(PROG2) 

matrix_mult_MP: matrix_mult_MP.o
	$(CC) $(CFLAGS) -o matrix_mult_MP matrix_mult_MP.o

matrix_mult_MP.o: matrix_mult_MP.c  
	$(CC) $(CFLAGS) -c matrix_mult_MP.c

# matrix_mult_MP.h




# primMT: primtMT.o
# 	$(CC) $(CFLAGS) -o primtMT primtMT.o 


# primtMT.o: primtMT.c  
# 	$(CC) $(CFLAGS) -c  primtMT.c  

clean:
	rm -f $(PROG1)  *.o *.gch 
# $(PROG2)
