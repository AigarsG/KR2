CC = gcc
CFLAGS = -Wall --std=c89
CFLAGS += -Iinclude

ODIR = obj
_OBJ = minunit.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(ODIR)/%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf main $(ODIR)/*


