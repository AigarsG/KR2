PROJECT_NAME = exercise5.18-5.20
export PROJECT_NAME

CC = gcc
CFLAGS = -Wall --std=c89 -Iinclude -I../utils/include
# for valgrind
CFLAGS += -g -O0

SRC = $(PROJECT_NAME).c
OBJ = $(SRC:.c=.o)

all: $(OBJ) dclcontext.o tests

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

dclcontext.o: dclcontext.c
	$(CC) $(CFLAGS) -c $^ -o $@

tests: $(OBJ)
	$(MAKE) -C tests

clean:
	@ $(MAKE) clean -C tests
	@ rm -f $(OBJ)

.PHONY: clean tests
