CC = gcc
CFLAGS = -Wall --std=c89
CFLAGS += -Iinclude
CFLAGS += -I../utils/include
CFLAGS += -I../minunit/include
VPATH = :../utils
VPATH += :../minunit

ODIR = obj
_OBJ = exercise2.04.o utils.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(ODIR)/%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*


