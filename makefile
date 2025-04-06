# Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = grafo
SRC = graph.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
