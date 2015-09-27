cc = gcc
cflags = -Wall
debugflags = -g

exes = ep2 memoryManager
objs = ep2.o memoryManager.o linkedList.o process.o

all: ep2 memoryManager

memoryManager: memoryManager.o linkedList.o process.o
	$(cc) -o $@ $^
	
ep2: ep2.o -lreadline
	$(cc) -o $@ $^

%.o: %.c linkedList.h
	$(cc) -c $(debugflags) $<

clean:
	-rm -f $(exes) $(objs) *~ core*