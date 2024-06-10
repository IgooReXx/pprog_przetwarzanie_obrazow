CC=gcc
CFLAGS=-std=c99 -pedantic -Wall
DEPS = display.h read_write.h rozc.h zamiana.h struktura.h opcje.h rozcpgm.c zamiana.c ppmtopgm.o
OBJ = main.o display.o read_write.o rozc.o zamiana.o opcje.o struktura.o rozcpgm.o zamianapgm.o ppmtopgm.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

przetwarzanie_obrazow: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
