C=gcc
AFLAGS=-Wall -g  
OBJS=jpeg.cgi
run:$(OBJS)

$(OBJS):%.cgi:%.c
		$(CC) $(AFLAGS) $< jpeg.c test.c -o $@
.PHONY:clean
	clean:
		rm *.o
