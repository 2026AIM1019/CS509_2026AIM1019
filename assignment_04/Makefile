CXX=g++
CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -pedantic
TARGET=a4_driver
SRC=driver/main.cpp src/graph_io.cpp src/color.cpp src/pagerank.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
