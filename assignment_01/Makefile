# Makefile for the LeetCode-style driver
# Usage:
#   make        -> build the driver binary
#   make run    -> build and run all test cases
#   make clean  -> remove the built binary

CXX      := g++
CXXFLAGS := -O2 -std=c++17 -Wall -Wextra
TARGET   := driver/driver
SRC      := driver/driver.cpp src/matmul.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean

