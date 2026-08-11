CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -O2

INCLUDES = -Isrc

TARGET = graph_runner

SOURCES = \
	driver/main.cpp \
	src/runner.cpp \
	src/graph_io.cpp \
	src/csr.cpp \
	src/bellman_ford.cpp \
	src/floyd_warshall.cpp \
	src/output.cpp \
	src/compare.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
