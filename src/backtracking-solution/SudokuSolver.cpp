//implementation file for sudoku-solver
#include "SudokuSolver.hpp"

//constructor
SudokuSolver::SudokuSolver(std::string fileName) {
  std::ifstream inputFile;

  //open file and read it into the Board
  inputFile.open(fileName.c_str());

  if(!inputFile) {
    cout << "Error: Filename invalid." << endl;
  }
  else {
    for(int row = 0; row < MAX_ROWS; row++) {
      for(int col = 0; col < MAX_COLS; col++) {
        inputFile >> sudokuBoard.contents[row][col];
      }
    }
  }
  inputFile.close();

  //set finished to false
  finished = false;
}




void SudokuSolver::solvePuzzle() {
  int correctValues[NUM_OF_ELEMENTS];
  int currcorrval = -1;
  backtrack(correctValues, currcorrval);
}


void SudokuSolver::backtrack(int correctValues[], int currcorrval) {

	int candidates[NUM_OF_ELEMENTS]; //stores candidates
	int nCandidates; // # of candidates


	if(isSolution(correctValues, currcorrval))//base case
    	processSolution(correctValues, currcorrval); //set finished to true, print the board - we are done

  else {
  	  currcorrval ++;
    findCandidates(correctValues, currcorrval, candidates, nCandidates);//
       //find most attractive square
    	 //find the number of possible solutions for most attractive square
    	 //set candidates
       //updates the number of candidates
    	//


    for(int i = 0; i < nCandidates; i++) {//loop through candidates
      correctValues[currcorrval] = candidates[i];
      makeMove(correctValues, currcorrval); //fills the square with the possible solution
      backtrack(correctValues, currcorrval); //continue along the board
      if(finished)
        return; //we found a solution, exit
      else
        unmakeMove(correctValues, currcorrval); //well, it was incorrect, empty the square

    }

  }
}

/*
Description: Checks if the board is a solution
*/

bool SudokuSolver::isSolution(int correctvalues[], int currcorrval)
{
 //if there are open spots, this won't do anything


  //example in isSoluton

/*  for i in corrLoStor array
    int row = sudokuBoard.corrLoStor[0].x //the row of the location of the square that the correct value fills
    int col = sudokuBoard.corrLoStor[0].y
    check sudokuBoard[row][col] for correctness
*/
  return false;
}



/*
Description:
*/
void SudokuSolver::findCandidates(int correctvalues[], int currcorrval, int candidates[], int &nCandidates)
{ }


/*
Description:
*/
void SudokuSolver::processSolution(int correctvalues[], int currcorrval)
{ }


/*
Description:
*/
void SudokuSolver::makeMove(int correctvalues[], int currcorrval)
{
/*
    //example make move
  sudokuBoard.contents[correctRow][correctCol] = currectvalues[currcorval];
  sudokuBoard.corrLoStor[currcorval].x = correctRow;
  sudokuBoard.corrLoStor[currcorval].y = correctCol;
*/

}


/*
Description:
*/
void SudokuSolver::unmakeMove(int correctvalues[], int currcorrval)
{ }

/*
Description: FOR TESTING PURPOSES ONLY
*/

void SudokuSolver::print() {
  for(int row = 0; row < MAX_ROWS; row++) {
    cout << endl;
    for(int col = 0; col < MAX_COLS; col++) {
      cout << sudokuBoard.contents[row][col] << " ";
    }
  }
  //briefly pause program
  cout << endl << "Press enter to continue the program...";
  std::cin.ignore();
}
