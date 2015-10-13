cc = gcc
cflags = -Wall
debugflags = -g

exes = ep2
objs = ep2.o memoryManager.o linkedList.o process.o simulador.o memory.o
headers = memoryManager.h linkedList.h process.h simulador.h memory.h

all: ep2
	
ep2: $(objs) -lreadline -lpthread
	$(cc) -o $@ $^

%.o: %.c $(headers)
	$(cc) -c $(debugflags) $<

clean:
	-rm -f $(exes) $(objs) *~ core*