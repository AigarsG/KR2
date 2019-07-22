PROJECT_NAME = exercise5.10
export PROJECT_NAME

CC = gcc
CFLAGS = -Wall --std=c89 -Iinclude -I../utils/include -I../exercise4.03/include

SRC = $(PROJECT_NAME).c
OBJ = $(SRC:.c=.o)

all: $(OBJ) $(PROJECT_NAME) tests

$(PROJECT_NAME): $(OBJ) ../exercise4.03/exercise4.03.o
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

tests: $(OBJ)
	$(MAKE) -C tests

clean:
	@ $(MAKE) clean -C tests
	@ rm -f $(OBJ) $(PROJECT_NAME)

.PHONY: clean tests

