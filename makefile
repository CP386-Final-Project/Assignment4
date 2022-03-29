CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread
TARGET = a4_q1
OBJFILES = a4_q1.o
all: $(TARGET)
a4_q1: a4_q1.c
	$(CC) $(CFLAGS) -o a4_q1 a4_q1.c $(LDFLAGS) 
	
runq1: a4_q1
	./a4_q1 10 5 7 8
clean:
	rm -f $(OBJFILES) $(TARGET) *~ 
