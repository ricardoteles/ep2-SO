cc = gcc
cflags = -Wall
debugflags = -g

exes = ep2
objs = ep2.o memoryManager.o linkedList.o process.o

all: ep2
	
ep2: $(objs) -lreadline
	$(cc) -o $@ $^

%.o: %.c memoryManager.h linkedList.h process.h
	$(cc) -c $(debugflags) $<

clean:
	-rm -f $(exes) $(objs) *~ core*