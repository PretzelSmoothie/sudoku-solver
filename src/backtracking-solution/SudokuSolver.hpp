//header file for sudoku-solver object
//Uses a backtracking algorithm to solve the puzzle

#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP

#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::endl;

class SudokuSolver {
private:

  struct LocationonBoard {
    int row;
    int col;
  };

  struct Board {
    int contents[9][9]; //this is sudoku puzzle we are solving
    int openSquares = 0; //num of open spots avail.
    LocationonBoard corrLoStor[81];//1D index of squares an array of x and y coordinates for a given position
  };

  Board sudokuBoard;
  bool finished;
  const int NUM_OF_ELEMENTS = 81;
  const int MAX_ROWS = 9;
  const int MAX_COLS = 9;

public:
  SudokuSolver(std::string fileName);//also should initialize board, set finish to false
  void solvePuzzle(); //call backtrack - helper method
  void backtrack(int correctvalues[], int currCorrVal);
  bool isSolution(int correctvalues[], int currCorrVal);
  void findCandidates(int correctvalues[], int currCorrVal, int candidates[], int &nCandidates);
  void processSolution(int correctvalues[], int currCorrVal);
  void makeMove(int correctvalues[], int currCorrVal);
  void unmakeMove(int correctvalues[], int currCorrVal);
  void print(); //for testing purposes


};

#endif
