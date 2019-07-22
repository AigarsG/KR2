PROJECT_NAME = exercise5.14
export PROJECT_NAME

CC = gcc
CFLAGS = -Wall --std=c89 -Iinclude -I../utils/include
# for valgrind
CFLAGS += -g -O0

SRC = $(PROJECT_NAME).c
OBJ = $(SRC:.c=.o)

all: $(PROJECT_NAME) tests

$(PROJECT_NAME): $(OBJ) ../utils/utils.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

tests: $(OBJ)
	$(MAKE) -C tests

clean:
	@ rm -f $(OBJ) $(PROJECT_NAME)
	@ $(MAKE) clean -C tests

.PHONY: clean tests
