ENVLAD := $(shell command -v ladcomp 2> /dev/null)

SDIR = ./src

CC = gcc
MPI = mpicc
LAD = ladcomp

LADFLAGS = -env mpicc
CFLAGS = -Wall -g

all: sequential.o parallel.o

sequential.o: $(SDIR)/sequential.c
	$(CC) -o $@ $< $(CFLAGS)

parallel.o: $(SDIR)/parallel.c
ifndef ENVLAD
	$(MPI) -o $@ $< $(CFLAGS)
else
	$(LAD) $(LADFLAGS) $< -o $@ $(CFLAGS)
endif


.PHONY: clean

clean:
	rm -rf sequential.o
	rm -rf parallel.o