PROJECT_NAME = exercise5.05
export PROJECT_NAME

CC = gcc
CFLAGS = -Wall --std=c89 -Iinclude -I../utils/include

SRC = $(PROJECT_NAME).c
OBJ = $(SRC:.c=.o)

all: $(OBJ) tests

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJ)
	$(MAKE) -C tests

clean:
	@ $(MAKE) clean -C tests
	@ rm -f $(OBJ)

.PHONY: clean tests

