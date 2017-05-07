CC = gcc
CFLAGS = -Wall -g

all: huffkoder huffdekoder

huffkoder: huffkoder.c
	$(CC) $(CFLAGS) -o huffkoder huffkoder.c
	
huffdekoder: huffdekoder.c
	$(CC) $(CFLAGS) -o huffdekoder huffdekoder.c
	
clean:
	-rm -f huffkoder huffdekoder *.o *.core
