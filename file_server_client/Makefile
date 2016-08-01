CC=gcc
CFLAGS=-Wall -g  -c 

all:server client

client:client.o
	$(CC) client.o -o $@
client.o:client.c 
	$(CC) $(CFLAGS) client.c -o $@

server:server.o
	$(CC) server.o -o $@
server.o:server.c
	$(CC) $(CFLAGS) server.c  -o $@

.PHONY:
	clean
clean:
	rm *.o  -rf
	cp  client server /home/linux/test/


