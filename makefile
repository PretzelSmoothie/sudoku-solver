all: solveSudoku

solveSudoku: testMain.o SudokuSolver.o
	g++ -g testMain.o SudokuSolver.o -o solveSudoku

testMain.o: tests/testMain.cpp src/SudokuSolver.hpp
	g++ -c tests/testMain.cpp

SudokuSolver.o: src/SudokuSolver.cpp src/SudokuSolver.hpp
	g++ -c src/SudokuSolver.cpp


clean:
	rm -f *.o
