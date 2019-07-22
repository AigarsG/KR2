#!/bin/bash


if [ $# -ne 1 ]; then
	echo "Creates a project directory with basic Makefile and source file"
	echo "Usage: ./create_project.sh project_based_dir"
	echo "Example: ./.create_project.sh exercise1.16"
	exit 1
fi


set -e


BASEDIR=$(dirname $BASH_SOURCE)


source "$BASEDIR/common"


PROJECT_BASE_GUARD=$(f_get_project_baseguard "$1")


# File contents
SOURCE_CONTENT="#include <stdio.h>
#include \"utils.h\"
#include \"$1.h\"


int replace_me(void)
{
\treturn 1;
}
"

TEST_SOURCE_CONTENT="#include \"CppUTest/CommandLineTestRunner.h\"
#include \"CppUTest/TestHarness.h\"

extern \"C\" {
#include \"$1.h\"
}


TEST_GROUP(group_1)
{
\tint ret;
};


TEST(group_1, test_1)
{
\tret = replace_me();
\tLONGS_EQUAL(0, ret);
}


int main(int argc, char** argv)
{
\treturn CommandLineTestRunner::RunAllTests(argc, argv);
}
"

MAKEFILE_CONTENT="PROJECT_NAME = $1
export PROJECT_NAME

CC = gcc
CFLAGS = -Wall --std=c89 -Iinclude -I../utils/include
# for valgrind
CFLAGS += -g -O0

SRC = \$(PROJECT_NAME).c
OBJ = \$(SRC:.c=.o)

all: \$(OBJ) tests

\$(OBJ): \$(SRC) ../utils/utils.o
\t\$(CC) \$(CFLAGS) -c \$^ -o \$@

tests: \$(OBJ)
\t\$(MAKE) -C tests

clean:
\t@ \$(MAKE) clean -C tests
\t@ rm -f \$(OBJ)

.PHONY: clean tests
"

TEST_MAKEFILE_CONTENT="CPPUTEST_HOME = ../../cpputest-3.8
CXX = g++
CXXFLAGS = -I../include -I\$(CPPUTEST_HOME)/include -I../../utils/include
CXXFLAGS += -include \$(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include \$(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

LDFLAGS += -L\$(CPPUTEST_HOME)/lib
LIBS += -lCppUTest

SRC = \$(PROJECT_NAME)_test.cpp
OBJ = \$(SRC:.cpp=.o)
TARGET = \$(PROJECT_NAME)_test

ifneq (, \$(shell which valgrind))
RUNPREFIX = valgrind --log-file=valgrind.log --leak-check=full 
endif

default: \$(TARGET) run

\$(TARGET): \$(OBJ) ../\$(PROJECT_NAME).o ../../utils/utils.o
\t@ \$(CXX) \$(CXXFLAGS) \$(LDFLAGS) \$^ -o \$@ \$(LIBS)

\$(OBJ): \$(SRC)
\t@ \$(CXX) \$(CXXFLAGS) -c \$< -o \$@

run: \$(TARGET)
\t./\$<

clean:
\t@ rm -f \$(TARGET) \$(OBJ)

.PHONY: clean run
"

# Replace '.' in project name with '_' and make it upper case
HEADER_GUARD="${PROJECT_BASE_GUARD}_HEADER"
HEADER_CONTENT="#ifndef ${HEADER_GUARD}
#define ${HEADER_GUARD}

int replace_me(void);

#endif"


# Create files and directories
f_create_file_or_dir 'dir' "$BASEDIR/$1"
f_create_file_or_dir 'dir' "$BASEDIR/$1/include"
f_create_file_or_dir 'dir' "$BASEDIR/$1/tests"
f_create_file_or_dir 'file' "$BASEDIR/$1/Makefile"
f_create_file_or_dir 'file' "$BASEDIR/$1/$1.c"
f_create_file_or_dir 'file' "$BASEDIR/$1/include/$1.h"
f_create_file_or_dir 'file' "$BASEDIR/$1/tests/$1_test.cpp"
f_create_file_or_dir 'file' "$BASEDIR/$1/tests/Makefile"


# Populate source file with base content
echo -e "$SOURCE_CONTENT" > "$BASEDIR/$1/$1.c"
echo -e "$TEST_SOURCE_CONTENT" > "$BASEDIR/$1/tests/$1_test.cpp"

# Populate Makefile with base content
echo -e "$MAKEFILE_CONTENT" > "$BASEDIR/$1/Makefile"
echo -e "$TEST_MAKEFILE_CONTENT" > "$BASEDIR/$1/tests/Makefile"

# Populate header fail with base content
echo -e "$HEADER_CONTENT" > "$BASEDIR/$1/include/$1.h"

