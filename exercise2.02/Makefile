CC = gcc
CFLAGS = -Wall --std=c89
CFLAGS += -Iinclude
CFLAGS += -I../utils/include
VPATH = :../utils

ODIR = obj
_OBJ = exercise2.02.o utils.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(ODIR)/%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*


