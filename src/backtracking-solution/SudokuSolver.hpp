//header file for sudoku-solver object
//Uses a backtracking algorithm to solve the puzzle

#ifndef SUDOKUSOLVER_HPP
#define SUDOKUSOLVER_HPP

#include <iostream>

class SudokuSolver {
private:

  struct Point {
    int x;
    int y;
  };

  struct Board {
    int contents[9][9];
    int openSquares;
    Point move[81];
  };

  bool finished;

public:
  SudokuSolver(std::string fileName);
  void backtrack(int arr[], int k, Board *sBoard);
  bool isSolution(int arr[], int k, Board *sBoard);
  void findPossibilities(int arr[], int k, Board *sBoard, int c[], int *nCandidates);
  void processSolution(int arr[], int k, Board *sBoard);
  void makeMove(int arr[], int k, Board *sBoard);
  void unmakeMove(int arr[], int k, Board *sBoard);


};

#endif
