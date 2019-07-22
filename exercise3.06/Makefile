CC = gcc
CFLAGS = -Wall --std=c89 -D EXERCISE3_06_TEST
CFLAGS += -Iinclude
CFLAGS += -I../utils/include
CFLAGS += -I../minunit/include
VPATH = :../utils
VPATH += :../minunit

ODIR = obj
_OBJ = exercise3.06.o utils.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(ODIR)/%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*

