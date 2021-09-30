#############################################################################
# File name:  Makefile
# Author:     chadd williams
# Date:       Sept 1, 2021
# Class:      CS360
# Assignment: 
# Purpose:    
#############################################################################

all: bin bin/httpget_large

bin:
	mkdir -p bin

bin/httpget_large: bin/httpget_large.o
	gcc -o bin/httpget_large -g -Wall bin/httpget_large.o

bin/httpget_large.o: bin src/httpget_large.c
	gcc -c -o bin/httpget_large.o -g -Wall src/httpget_large.c


clean:
	rm -f bin/httpget_large bin/*.o
