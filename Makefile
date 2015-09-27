cc = gcc
cflags = -Wall
debugflags = -g

exes = ep2 simulador
objs = ep2.o simulador.o linkedList.o

all: ep2 simulador

simulador: simulador.o linkedList.o
	$(cc) -o $@ $^
	
ep2: ep2.o -lreadline
	$(cc) -o $@ $^

%.o: %.c linkedList.h
	$(cc) -c $(debugflags) $<

clean:
	-rm -f $(exes) $(objs) *~ core*