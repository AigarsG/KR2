CC = gcc
CFLAGS = -Wall --std=c89
CFLAGS += -Iinclude
CFLAGS += -I../utils/include

ODIR = obj
_OBJ = exercise1.22.o utils.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(ODIR)/exercise1.22.o: exercise1.22.c 
	$(CC) $(CFLAGS) -o $@ -c $<

$(ODIR)/utils.o: ../utils/utils.c
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*


