# Makefile para Tarea2Algoritmos

# Variables
CC = g++
CFLAGS = -O3
SRC = main.cpp editDistanceDP.cpp editDistanceDPOptimized.cpp editDistanceMemo.cpp editDistanceRecursive.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = editDistance

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean