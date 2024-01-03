CC = gcc
CFLAGS = -Wall -g

download-cleaner:
	 $(CC) $(CFLAGS) download-cleaner.c -o download-cleaner

clean:
	rm -rf download-cleaner
