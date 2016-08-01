CC=gcc
CFLAGS= -lsqlite3 

all:server client


client:client.c
	    $(CC) client.c $(CFLAGS) -o $@
server:server.c
	    $(CC) server.c $(CFLAGS)  -o $@

.PHONY:
	    clean
clean:
	    rm server client
