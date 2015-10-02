cc = gcc
cflags = -Wall
debugflags = -g

exes = ep2
objs = ep2.o memoryManager.o linkedList.o process.o prompt.o

all: ep2
	
ep2: $(objs) -lreadline -lpthread
	$(cc) -o $@ $^

%.o: %.c memoryManager.h linkedList.h process.h prompt.h
	$(cc) -c $(debugflags) $<

clean:
	-rm -f $(exes) $(objs) *~ core*