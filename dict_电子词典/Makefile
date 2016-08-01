CC=gcc
CFLAGS= -lsqlite3 

all:server client


client:dict_client.c
	    $(CC) dict_client.c $(CFLAGS) -o $@
server:dict_server.c
	    $(CC) dict_server.c $(CFLAGS)  -o $@

.PHONY:
	    clean
clean:
	    rm *.o  -rf 
