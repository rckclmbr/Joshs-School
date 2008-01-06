CC=gcc
CFLAGS=-Wall -ggdb

all : conman conman-listener conman-server
conman: conman.c shared.o
conman-listener : conman-listener.c shared.o
conman-server : conman-server.c shared.o
shared.o : shared.c

clean :
	@rm conman conman-server conman-listener *.o
