PROJECT_NAME = utils
export PROJECT_NAME


CC = gcc
CFLAGS = -Wall --std=c89 -Iinclude
# for valgrind
CFLAGS += -g -O0
SRC = $(PROJECT_NAME).c
OBJ = $(SRC:.c=.o)


all: $(OBJ) tests

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

tests: $(OBJ)
	$(MAKE) -C tests

clean:
	@ $(MAKE) clean -C tests
	@ rm -f $(OBJ)

.PHONY: clean tests
