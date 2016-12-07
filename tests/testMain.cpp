//simple method test for SudokuSolver

#include <iostream>
#include "../src/SudokuSolver.hpp"


using namespace std;

int main() {
  SudokuSolver sudokuBoard("tests/easy1.dat");
/*
  sudokuBoard.print();
  bool testPossible[10];
  memset(testPossible, true, 10);
  sudokuBoard.findPossibilites(8, 6, testPossible);

  for(int i = 1; i < 10; i++) {
    cout << i << ": ";
    if(testPossible[i]) { cout << "possible"; }
    else { cout << "Impossible"; }
    cout << endl;
  }*/

  sudokuBoard.solvePuzzle();

/*
  sudokuBoard.printOpenSpots();*/

  sudokuBoard.print();

  return 0;
}
