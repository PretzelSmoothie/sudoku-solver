//header file for sudoku-solver object
//Uses a backtracking algorithm to solve the puzzle

#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;


class SudokuSolver {
private:

	struct LocationBoard {
		int x;
		int y;
	};

	struct Board {
		Board() { openSquares = 0; }
		int contents[9][9]; //this is sudoku puzzle we are solving
		int openSquares; //num of open spots avail.
		LocationBoard corrLoStor[81];//1D index of squares an array of x and y coordinates for a given position
	};
	LocationBoard openSpots[81];
	int correctValues[81];
	int currCorrVal;
	Board sudokuBoard;
	bool finished;
	int NUM_OF_ELEMENTS;
	int MAX_ROWS;
	int MAX_COLS;
	int MAX_POSSIBLE;


public:
	SudokuSolver(std::string fileName);//also should initialize board, set finish to false
	void solvePuzzle();
	bool isSolution();
	void findCandidates(int candidates[], int &nCandidates);
	void processSolution();
	void makeMove();
	void unmakeMove();
	void findNextSquare(int& row, int& col);
	void findPossibilites(const int row, const int col, bool possible[]);
	void getCluster(const int row, const int col, int& rowBegin, int& rowEnd, int& colBegin, int& colEnd);
	void print();
	void printOpenSpots();


};

#endif
