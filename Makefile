CC = g++
CFLAGS = --std=c++11 -Wall -c
LFLAGS = --std=c++11
SRC = src
OBJ = obj
DOC = doc

all: sudoku

sudoku: $(OBJ)/main.o $(OBJ)/sudoku.o
	$(CC) $(LFLAGS) $(OBJ)/main.o $(OBJ)/sudoku.o -o sudoku

$(OBJ)/main.o: $(SRC)/main.cpp $(SRC)/sudoku.hpp
	$(CC) $(CFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

$(OBJ)/sudoku.o: $(SRC)/sudoku.cpp $(SRC)/sudoku.hpp
	$(CC) $(CFLAGS) $(SRC)/sudoku.cpp -o $(OBJ)/sudoku.o

.PHONY: clean doc test

doc:
	doxygen doxyfile

clean:
	rm -rf $(OBJ)/* $(DOC)/* sudoku
