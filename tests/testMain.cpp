//simple method test for SudokuSolver

#include <iostream>
#include "../src/SudokuSolver.hpp"


using namespace std;

int main() {
  string fileName;
  int menuChoice = 0;

  cout << endl << "Welcome to SudokuSolver!!";

  while(menuChoice < 1 || menuChoice > 4) {
    cout << endl << "Please select one of the below test boards:" << endl
         << "1. easy" << endl
         << "2. medium" << endl
         << "3. hard" << endl
         << "4. expert" << endl
         << "Choice: ";
         cin >> menuChoice;
         cin.ignore();
    switch(menuChoice) {
      case 1:
        fileName = "tests/easy.dat";
        break;
      case 2:
        fileName = "tests/medium.dat";
        break;
      case 3:
        fileName = "tests/hard.dat";
        break;
      case 4:
        fileName = "tests/expert.dat";
        break;
      default:
        cout << endl << "Please, enter a valid choice.";
        break;
    }
  }


  SudokuSolver puzzle(fileName);
  cout <<"Unsolved board:";
  puzzle.print();
  cout << "Now solving board...";
  puzzle.solvePuzzle();

  return 0;
}
