CPPUTEST_HOME = ../../cpputest-3.8
CXX = g++
CXXFLAGS = -I../include -I$(CPPUTEST_HOME)/include
CXXFLAGS += --include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += --include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

LDFLAGS += -L$(CPPUTEST_HOME)/lib
LIBS += -lCppUTest

SRC = $(PROJECT_NAME)_test.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = $(PROJECT_NAME)_test

default: $(TARGET) run

$(TARGET): $(OBJ) ../$(PROJECT_NAME).o ../../utils/utils.o
	@ $(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

$(OBJ): $(SRC)
	@ $(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$<

clean:
	@ rm -f $(TARGET) $(OBJ)

.PHONY: clean run

