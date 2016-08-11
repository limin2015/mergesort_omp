CC = gcc

# openmp compiler option for gcc
CFLAGS = -fopenmp

all: mergesort

mergesort: mergesort.c merge.o
	$(CC) -o mergesort $(CFLAGS) mergesort.c merge.o

merge.o: merge.c
	$(CC) -c merge.c

clean:
	rm -f mergesort merge.o
