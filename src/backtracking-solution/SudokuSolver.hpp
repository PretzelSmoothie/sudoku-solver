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

enum Cluster {Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9};


class SudokuSolver {
private:

  struct LocationonBoard {
    int x;
    int y;
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
  const int MAX_POSSIBLE = 10;


public:
  SudokuSolver(std::string fileName);//also should initialize board, set finish to false
  void solvePuzzle(); //call backtrack - helper method
  void backtrack(int correctvalues[], int currCorrVal);
  bool isSolution(int correctvalues[], int currCorrVal);
  void findCandidates(int correctvalues[], int currCorrVal, int candidates[], int &nCandidates);
  void processSolution(int correctvalues[], int currCorrVal);
  void makeMove(int correctvalues[], int currCorrVal);
  void unmakeMove(int correctvalues[], int currCorrVal);
  void findNextSquare(int& row, int& col);
  void findPossibilites(const int row, const int col, bool possible[]);
  void getCluster(const int row, const int col, int& rowBegin, int& rowEnd, int& colBegin, int& colEnd);
  void print();


};

#endif
