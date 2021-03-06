# Makefile for CPU diffusion code
# Analytical solution

CC = gcc
CFLAGS = -O3 -Wall -pedantic -I. -I../common-diffusion
LINKS = -lm -lpng

OBJS = discretization.o mesh.o numerics.o output.o timer.o

all: diffusion

.PHONY: all compare run clean cleanobjects cleanoutputs cleanall

diffusion: main.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@ $(LINKS)

discretization.o: discretization.c
	$(CC) $(CFLAGS) -c $<

mesh.o: ../common-diffusion/mesh.c
	$(CC) $(CFLAGS) -c $<

numerics.o: ../common-diffusion/numerics.c
	$(CC) $(CFLAGS) -c $<

output.o: ../common-diffusion/output.c
	$(CC) $(CFLAGS) -c $<

timer.o: ../common-diffusion/timer.c
	$(CC) $(CFLAGS) -c $<

run: diffusion
	/usr/bin/time -f' Time (%E wall, %U user, %S sys)' ./diffusion ../common-diffusion/params.txt

compare: run
	composite diffusion.0100000.png ../common-diffusion/diffusion.10000.png -compose difference delta.png

cleanobjects:
	rm -f diffusion *.o

cleanoutputs:
	rm -f delta.png diffusion.*.csv diffusion.*.png runlog.csv

clean: cleanobjects

cleanall: cleanobjects cleanoutputs
