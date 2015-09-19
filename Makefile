cc = gcc
cflags = -Wall
debugflags = -g

execs = ep2
obj = ep2.o

all: ep2

ep2: ep2.o -lreadline
	$(cc) -o $@ $^	

%.o: %.c
	$(cc) -c $(debugflags) $<

clean: 
	-rm -f $(execs) $(obj) *~ core*