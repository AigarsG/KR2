CC = gcc
CFLAGS = -Wall --std=c89

UDIR = ../utils
IDIR = $(UDIR)/include
_DEP = utils.h
DEP = $(patsubst %, $(IDIR)/%, $(_DEP))

ODIR = obj
_OBJ = main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

CFLAGS += -I$(IDIR)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(UDIR)/utils.c

.PHONY: clean
clean:
	rm -rf main $(ODIR)/*

