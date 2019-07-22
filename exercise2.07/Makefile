CC = gcc
CFLAGS = -Wall --std=c89 -D EXERCISE2_07_TEST

CFLAGS += -Iinclude
CFLAGS += -I../utils/include
CFLAGS += -I../minunit/include
CFLAGS += -I../exercise2.06/include
VPATH = :../utils
VPATH += :../minunit
VPATH += :../exercise2.06

ODIR = obj
_OBJ = exercise2.07.o utils.o exercise2.06.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(ODIR)/%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*

