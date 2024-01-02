CC = gcc
CFLAGS = -Wall -g

dc:
	 $(CC) $(CFLAGS) download-cleaner.c -o dc

clean:
	rm -rf dc
