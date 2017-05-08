CC = gcc
CFLAGS = -Wall -g

all: huffencoder huffdecoder

huffencoder: huffencoder.c
	$(CC) $(CFLAGS) -o huffencoder huffencoder.c
	
huffdecoder: huffdecoder.c
	$(CC) $(CFLAGS) -o huffdecoder huffdecoder.c
	
clean:
	-rm -f huffencoder huffdecoder *.o *.core
