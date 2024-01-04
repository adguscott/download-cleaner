CC = gcc
CFLAGS = -Wall -g

download-cleaner: download-cleaner.c download-cleaner.h common.h config.h
	 $(CC) $(CFLAGS) download-cleaner.c -o download-cleaner

clean:
	rm -rf download-cleaner
