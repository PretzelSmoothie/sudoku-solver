//implementation file for sudoku-solver
#include "SudokuSolver.hpp"

//constructor
SudokuSolver::SudokuSolver(std::string fileName) {
	std::ifstream inputFile;

	//open file and read it into the Board
	inputFile.open(fileName.c_str());
	int count = 0;//counter for corrLoStor array

	if (!inputFile) {
		cout << "Error: Filename invalid." << endl;
	}
	else {
		for (int row = 0; row < MAX_ROWS; row++) {
			for (int col = 0; col < MAX_COLS; col++)
			{
				inputFile >> sudokuBoard.contents[row][col];
				if (sudokuBoard.contents[row][col] == 0)//if incoming value is 0 - meaning empty
					sudokuBoard.openSquares++;//increase board openSquares by 1
				else//if the square comes in with a value, which must be correct
				{//add coordinates to corrLoStor[count]
					sudokuBoard.corrLoStor[count].x = row;
					sudokuBoard.corrLoStor[count].y = row;
					count++;//increase count by 1
				}
			}
		}
	}
	inputFile.close();
	for (int i = 0; i < count; i++)
	{
		cout << sudokuBoard.corrLoStor[i].x << ", " << sudokuBoard.corrLoStor[i].y << " ";
		cout << endl;
	}
	//set finished to false
	finished = false;
}




void SudokuSolver::solvePuzzle() {
	const int NUM_OF_ELEMENTS = 81;
	int correctValues[NUM_OF_ELEMENTS];
	int currcorrval = -1;
	backtrack(correctValues, currcorrval);
	cout << "enter solvePuzzle";
}


void SudokuSolver::backtrack(int correctValues[], int currcorrval) {
	const int NUM_OF_ELEMENTS = 81;
	int candidates[NUM_OF_ELEMENTS]; //stores candidates
	int nCandidates; // # of candidates


	if (isSolution(correctValues, currcorrval))//base case
		processSolution(correctValues, currcorrval); //set finished to true, print the board - we are done

	/*else {
		currcorrval++;
		findCandidates(correctValues, currcorrval, candidates, nCandidates);//
																			//find most attractive square
																			//find the number of possible solutions for most attractive square
																			//set candidates
																			//updates the number of candidates
																			//


		for (int i = 0; i < nCandidates; i++) {//loop through candidates
			correctValues[currcorrval] = candidates[i];
			makeMove(correctValues, currcorrval); //fills the square with the possible solution
			backtrack(correctValues, currcorrval); //continue along the board
			if (finished)
				return; //we found a solution, exit
			else
				unmakeMove(correctValues, currcorrval); //well, it was incorrect, empty the square

		}

	}
	*/
}

/*
Description: Checks if the board is a solution
*/

bool SudokuSolver::isSolution(int correctvalues[], int currcorrval)
{
	
	if (sudokuBoard.openSquares != 0)
	{
		cout << "OpenSquares is more than 0, returning false";
		return false;
	}
	else
	{
		for (int i = 0; i < 81; i++)//for each square location in correct storage location array
		{
			int row = sudokuBoard.corrLoStor[i].x; //get the row of the location of the square that the correct value fills
			int col = sudokuBoard.corrLoStor[i].y;//get the column of the location that the correct value fills
			int edgerow = 0;
			int edgecol = 0;
			

			//SECTION CONVERTS CLUSTER INTO A FLAT ARRAY
			//first finding correct 3 x 3 cluster edges
			if (row == 0 || row == 1 || row == 2)
				edgerow = 0;//sets edge parameter
			else if (row == 3 || row == 4 || row == 5)
				edgerow = 3;
			else 
				edgerow = 6;
			if (col == 0 || col == 1 || col == 2)
				edgecol = 0;
			else if (col == 3 || col == 4 || col == 5)
				edgecol = 3;
			else 
				edgecol = 6;
			//now converting part 3 x 3 int clusterArray [1-9]
			int clusterArray[9];
			int num = 0;
			for (int m = 0; m < 3; m++)
			{
				for (int q = 0; q < 3; q++)
				{
					clusterArray[num] = sudokuBoard.contents[m + edgerow][q + edgecol ];
					num++;
				}
			}


			std::vector<int> rowbank(9);//create new empty row to fill
			std::vector<int> colbank(9);//create new empty column to fill
			std::vector<int> clusterbank(9);//create new empty cluster to fill

			for (int j = 0; j < 9; j++)//process through row and column found above
			{
				rowbank[sudokuBoard.contents[row][j] - 1] = sudokuBoard.contents[row][j];//put value found in row[j] into empty row vector spot j
				colbank[sudokuBoard.contents[j][col] - 1] = sudokuBoard.contents[j][col];//put value found in column[j] into empty column vector spot j
				clusterbank[clusterArray[j] - 1] = clusterArray[j];//put value found in clustArrray[j] into empty cluster vector
			}

			for (int z = 0; z < 9; z++)//loop through bank vectors

			{
				if (rowbank[z] != z + 1 || colbank[z] != z + 1 || clusterbank[z] != z + 1)//i.e. if rowbank spot 2 doesn't = 2, or columnbank spot 2 doesn't = 2, or rowbanks spot 2 doesn't = 2
				{
					cout << "not a solution, returning false";
					return false;//then return false
				}
			}
		}
	}
	cout << " Is a solution, returning true";
	return true;
}

/*
Description:
*/
void SudokuSolver::processSolution(int correctvalues[], int currcorrval)
{
	finished = true;
	print();
}

/*
Description:
*/
void SudokuSolver::findCandidates(int correctvalues[], int currcorrval, int candidates[], int &nCandidates)
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
	for (int row = 0; row < MAX_ROWS; row++) {
		cout << endl;
		for (int col = 0; col < MAX_COLS; col++) {
			cout << sudokuBoard.contents[row][col] << " ";
		}
	}
	//briefly pause program
	cout << endl << "Press enter to continue the program...";
	std::cin.ignore();
}