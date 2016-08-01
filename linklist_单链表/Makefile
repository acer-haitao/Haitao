CC=gcc
CFLAGS=-Wall -g -c
OBJECT=test

$(OBJECT):linklist.o main.o
	$(CC)  $^ -o $@
%*.o:%*.c
	$(CC)  $^ -o $@

.PHONY:
		clean
clean:
		rm *.o 





