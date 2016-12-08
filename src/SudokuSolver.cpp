//implementation file for sudoku-solver
#include "SudokuSolver.hpp"
#include <cstring>

//constructor
SudokuSolver::SudokuSolver(std::string fileName) {
  std::ifstream inputFile;
  NUM_OF_ELEMENTS = 81;
  MAX_ROWS = 9;
  MAX_COLS = 9;
  MAX_POSSIBLE = 10;
  currCorrVal = -1;

  //open file and read it into the Board
  inputFile.open(fileName.c_str());

  if(!inputFile)
  {
    cout << "Error: Filename invalid." << endl;
  }
  else
  {
    for(int row = 0; row < MAX_ROWS; row++)
    {
      for(int col = 0; col < MAX_COLS; col++)
      {
        inputFile >> sudokuBoard.contents[row][col];
        if(sudokuBoard.contents[row][col] == 0)
        {
          sudokuBoard.openSquares++;
          openSpots[sudokuBoard.openSquares].x = row;
          openSpots[sudokuBoard.openSquares].y = col;
        }
      }
    }
  }
  inputFile.close();

  finished = false;
}

//start solving!
void SudokuSolver::solvePuzzle() {

	int candidates[81]; //stores square candidates
	int nCandidates; // # of candidates we have found

	if(isSolution()) { processSolution(); }

else
{
	  currCorrVal++;
    findCandidates(candidates, nCandidates);
    for(int i = 0; i < nCandidates; i++)
    {
      correctValues[currCorrVal] = candidates[i];
      makeMove();
      solvePuzzle();
  		if (finished) { return; } //we are done! Solution has been found
  		else
      {
  		  unmakeMove();
  		  currCorrVal--;
  		}
    }

  }
}




/*
Description: Checks if there is a solution to the board
*/

bool SudokuSolver::isSolution()
{

    if (sudokuBoard.openSquares != 0) { return false; }//if the board isn't full
    else//if the board is full
  	{
  		for (int i = 0; i < 9; i++)//for each row, column and cluster - outer of nested loop
  		{

  			std::vector<int> rowbank(9,0);//create new empty row to fill
  			std::vector<int> colbank(9,0);//create new empty column to fill
  			std::vector<int> clusterbank(9,0);//create new empty cluster to fill

  		    //SECTION CONVERTS CLUSTER INTO A FLAT ARRAY

  			int edgerow = 0;//Setting Edge parameters
  			int edgecol = 0;
  			edgecol = 3*((i + 3) % 3);

  			if (i == 3 || i == 4 || i ==5) { edgerow += 3; }
  			if (i == 6 || i == 7 || i == 8) { edgerow += 6; }

        int val = 0;
  			int clusterArray[9] = { 0,0,0,0,0,0,0,0,0 };//array that will hold cluster

        for (int m = 0; m < 3; m++)
  			{
  				for (int p = 0; p < 3; p++)
  				{
            //copying current cluster into flat cluster Array
  					clusterArray[val] = sudokuBoard.contents[m + edgerow][p+edgecol];
  					val++;
  				}
  			}

  			for (int j = 0; j < 9; j++)//puts number 1-9 into bank slot of number
  			{
  				rowbank[sudokuBoard.contents[i][j] - 1] = sudokuBoard.contents[i][j];
  				colbank[sudokuBoard.contents[j][i] - 1] = sudokuBoard.contents[j][i];
          //put value found in clustArrray[j] into empty cluster vector
  				clusterbank[clusterArray[j] - 1] = clusterArray[j];
  			}

  			for (int z = 0; z < 9; z++)//loop through bank vectors
  			{
  				if (rowbank[z] != z + 1 || colbank[z] != z + 1 || clusterbank[z] != z + 1)
  				{//if rowbank slot j doesn't = j, then false
  					return false;//then return false
  				}
  			}
  		}
  	}
  return true;
}




/*
Description:
*/
void SudokuSolver::findCandidates(int candidates[], int &nCandidates)
{
  int row, col; // Will store position of next move
  bool possible[10]; //what is possible for the current square
  memset(possible, true, MAX_POSSIBLE); //set all values to true for later

  //which square should we fill next?
  findNextSquare(row, col);

  //store the current row and column into the correct location storage
  sudokuBoard.corrLoStor[currCorrVal].x = row;
  sudokuBoard.corrLoStor[currCorrVal].y = col;


  nCandidates = 0;

  if(row < 0 && col < 0) { return; } //no moves possible, abort

  //What are the possible values for this square?
  findPossibilites(row, col, possible);


  //update nCandidates and Candidate array
  for(int i = 1; i <= 9; i++)
  {
    if(possible[i] == true)
    {
      candidates[nCandidates] = i;
      nCandidates++;
    }
  }
}


/*
Description: Print the broad and set finished to true, as we have solved the
             puzzle.
*/
void SudokuSolver::processSolution()
{
  finished = true;
  print();
}


/*
Description: Write the current candidate to the square we are looking at
*/
void SudokuSolver::makeMove()
{
  int correctRow = sudokuBoard.corrLoStor[currCorrVal].x;
  int correctCol = sudokuBoard.corrLoStor[currCorrVal].y;
  sudokuBoard.contents[correctRow][correctCol] = correctValues[currCorrVal];
  sudokuBoard.openSquares--;
}


/*
Description: In the case the number we tested for a square is wrong, reset it
             to zero.
*/
void SudokuSolver::unmakeMove()
{
  int correctRow = sudokuBoard.corrLoStor[currCorrVal].x;
  int correctCol = sudokuBoard.corrLoStor[currCorrVal].y;
  sudokuBoard.contents[correctRow][correctCol] = 0;
  sudokuBoard.openSquares++;
}

/*
Description: Finds the square with the least number of possibilities to attempt
             to find a solution for.
*/

void SudokuSolver::findNextSquare(int& row, int& col)
{
    int rowzeros[9];
  	int colzeros[9];
  	int clusterzeros[9];

    //SECTION GETS AND STORES TOTAL ZEROS FOR EACH ROW, COLUMN AND CLUSTER
  	for (int i = 0; i < 9; i++)//for each row, column and cluster - outer of nested loop
  	{
  		//SECTION CONVERTS CLUSTER INTO A FLAT ARRAY
  		int edgerow = 0;
  		int edgecol = 0;
  		edgecol = 3 * ((i + 3) % 3);

  		if (i == 3 || i == 4 || i == 5)
  			{ edgerow += 3; }
  		if (i == 6 || i == 7 || i == 8)
  			{ edgerow += 6; }

  		int val = 0;
  		int clusterArray[9] = { 0,0,0,0,0,0,0,0,0 };

  		for (int m = 0; m < 3; m++)
  		{
  			for (int p = 0; p < 3; p++)
  			{
  				clusterArray[val] = sudokuBoard.contents[m + edgerow][p + edgecol];
  				val++;
  			}
  		}
  		//END CONVERSION

  		int rowcount = 0;//counts zeros in row
  		int colcount = 0;
  		int cluscount = 0;

  		for (int j = 0; j < 9; j++)//process through row, column and cluster  - inner of nest loop
  		{
        //if spot in row is 0, add to 0 counter for row
  			if (sudokuBoard.contents[i][j] == 0) { rowcount++; }
  			if (sudokuBoard.contents[j][i] == 0) { colcount++; }
  			if (clusterArray[j] == 0) { cluscount++; }
  		}

  		rowzeros[i] = rowcount;//i.e. set row [1] to rowcount of row 1
  		colzeros[i] = colcount;
  		clusterzeros[i] = cluscount;

  	}
  	//END GET AND STORE TOTAL ZEROS FOR ROW, COLUMN, AND CLUSTER
  	//BEGIN FIND 0 SQUARE WITH LEAST ZERO VALUE
  	int minzeros = 81;//initialize min zeros
  	LocationBoard bestSquare;//initialize best square
  	int cluster = 0;//cluster tracker

  	for (int k = 0; k < 9; k++)//outer loop, loop through board rows
  	{
      //edge tracking for cluster
  		if ((k != 0) && ((k % 3) == 0)) { cluster += 3; }
      //loop through board columns
  		for (int h = 0; h < 9; h++)
  		{
        //edge tracking for cluster
  			if (h != 0 && h % 3 == 0)	{	cluster++; }

  			int totalzeros = 0;//initialize total zeros counter
  			int samezeros = 0;//initialze same zeros counter (to not double count 0s from the same cluster, if in the same row/col)
  			if (sudokuBoard.contents[k][h] == 0)//if the spot on the board is a zero
  			{
  				if ((h + 4) % 3 == 1)//get same zeros
  				{
  					if (sudokuBoard.contents[k][h+1] == 0) {	samezeros++;}
  					if (sudokuBoard.contents[k][h+2] == 0) {	samezeros++;}
  				}
  				else if ((h + 4) % 3 == 2)//get same zeros
  				{
  					if (sudokuBoard.contents[k][h + 1] == 0) { samezeros++;}
  					if (sudokuBoard.contents[k][h - 1] == 0) { samezeros++;}
  				}
  				else //get same zeros
  				{
  					if (sudokuBoard.contents[k][h - 1] == 0) { samezeros++;}
  					if (sudokuBoard.contents[k][h - 2] == 0) {	samezeros++;}
  				}
  				if ((k + 4) % 3 == 1)//get same zeros
  				{
  					if (sudokuBoard.contents[k + 1][h] == 0) {samezeros++;}
  					if (sudokuBoard.contents[k + 2][h] == 0) {samezeros++;}
  				}
  				else if ((k + 4) % 3 == 2)//get same zeros
  				{
  					if (sudokuBoard.contents[k + 1][h] == 0) {samezeros++;}
  					if (sudokuBoard.contents[k - 1][h] == 0) {samezeros++;}
  				}
  				else//get same zeros
  				{
  					if (sudokuBoard.contents[k - 1][h] == 0) {samezeros++;}
  					if (sudokuBoard.contents[k - 2][h] == 0) {samezeros++;}
  				}
  				totalzeros = rowzeros[k] + colzeros[h] + clusterzeros[cluster] - samezeros -3;//calculates how many other 0s are in the same row, column, and cluster,
  				if (totalzeros < minzeros)//if minimum zeros found so far is less than total zeros													  //not counting itself or other 0s in the same row and column of the cluster
  				{
  					minzeros = totalzeros;//set minzeros to total zeros
  					bestSquare.x = k;//set bestSquare to the current location
  					bestSquare.y = h;
  				}
  			}
  		}

  		cluster = cluster - 2;
  	}
  row = bestSquare.x;//set coordinates for the best square
  col = bestSquare.y;
}

/*
Description: Finds the possibiles numbers for a given empty square that we are
             examining.
*/

void SudokuSolver::findPossibilites(const int row, const int col, bool possible[])
{
  //check current row
  for(int i = 0; i < 9; i++)
  {
    if(sudokuBoard.contents[row][i] != 0)
    {
      possible[sudokuBoard.contents[row][i]] = false;
    }
  }

  //check current column
  for(int i = 0; i < 9; i++ )
  {
    if(sudokuBoard.contents[i][col] != 0)
    {
      possible[sudokuBoard.contents[i][col]] = false;
    }
  }

  //check current cluster
  int rowEnd, rowBegin, colEnd, colBegin;;
  getCluster(row, col, rowBegin, rowEnd, colBegin, colEnd);


  for(int i = rowBegin; i < rowEnd; i++)
  {
    for(int j = colBegin; j < colEnd; j++)
    {
      if(sudokuBoard.contents[i][j] != 0)
      {
        possible[sudokuBoard.contents[i][j]] = false;

      }
    }
  }

}

/*
Description: Find the current quadrant of the puzzle we are looking to examine
*/
void SudokuSolver::getCluster(const int row, const int col,
  int& rowBegin, int& rowEnd, int& colBegin, int& colEnd)
{
  if(row <= 2)
  {
    rowEnd = 3;
    rowBegin = 0;
    if(col <=2)
    {
      colBegin = 0;
      colEnd = 3;
     }
    else if(col >=3 && col <= 5)
    {
      colBegin = 3;
      colEnd = 6;
     }
    else if(col >= 6 && col <= 8)
    {
      colBegin = 6;
      colEnd = 9;
    }
  }

  else if(row >= 3 && row <= 5)
  {
    rowEnd = 6;
    rowBegin = 3;
    if(col <= 2)
    {
      colBegin = 0;
      colEnd = 2;
    }
    else if(col >= 3 && col <= 5)
    {
      colBegin = 3;
      colEnd = 6;
    }
    else if(col >= 6 && col <= 8)
    {
      colBegin = 6;
      colEnd = 9;
    }
  }

  else if(row >= 6 && row <= 8)
  {
    rowBegin = 6;
    rowEnd = 9;
    if(col <= 2)
    {
      colBegin = 0;
      colEnd = 3;
    }
    else if(col >= 3 && col <= 5)
    {
      colBegin = 3;
      colEnd = 6;
    }
    else if(col >= 6 && col <= 8)
    {
      colBegin = 6;
      colEnd = 9;
     }
  }
}

/*
Description: Prints board, pauses at the end for user input
*/

void SudokuSolver::print() {
  for(int row = 0; row < MAX_ROWS; row++)
  {
    cout << endl;
    for(int col = 0; col < MAX_COLS; col++)
    {
      cout << sudokuBoard.contents[row][col] << " ";
    }
  }
  //briefly pause program
  cout << endl << "Press enter to continue this program...";
  std::cin.ignore();
}

/*
Description:  Prints the location of the open spots in the puzzle, primarily
              for testing purposes.
*/

void SudokuSolver::printOpenSpots()
{
  for(int i = 1; i < sudokuBoard.openSquares; i++)
  {
    cout << endl << "Row: " << openSpots[i].x
         << "Col: " << openSpots[i].y;
  }
  //briefly pause program
  cout << endl << "Press enter to continue this program...";
  std::cin.ignore();
}
