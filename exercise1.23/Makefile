CC = gcc
CFLAGS = -Wall --std=c89
CFLAGS += -Iinclude
CFLAGS += -I../utils/include
CFLAGS += -I../exercise1.22/include
VPATH = :../utils
VPATH += :../exercise1.22
LDFLAGS=-Wl,--allow-multiple-definition    # allow multiple definitions of main

ODIR = obj
_OBJ = exercise1.23.o utils.o exercise1.22.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*


