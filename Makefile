# Makefile for assignment 1 OMP - Parallel Programming
# Author: Ian Wilkes

CC=gcc
CFLAGS=-fopenmp -Wall -g -O0 -std=c99

all: filter.o

filter.o: filter.c
	$(CC) $(CFLAGS) -o filter filter.c

clean:
	rm -rf filter *.o
