CC=gcc

all:scheduler

scheduler: scheduler.o MyQueue.o functions.o
	$(CC) -o scheduler scheduler.o MyQueue.o functions.o

functions.o: functions.c functions.h
	$(CC) -c functions.c
MyQueue.o: MyQueue.c MyQueue.h
	$(CC) -c MyQueue.c
scheduler.o:scheduler.c functions.h MyQueue.h
	$(CC) -c scheduler.c

clean:
	rm -f scheduler *.o core*
