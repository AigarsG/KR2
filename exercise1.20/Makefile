CC = gcc
CFLAGS = -Wall --std=c89

ODIR = obj
_OBJ = main.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $^

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -rf main $(ODIR)/*

