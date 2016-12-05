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
					sudokuBoard.corrLoStor[count].y = col;
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
	//const int NUM_OF_ELEMENTS = 81;
	//int candidates[NUM_OF_ELEMENTS]; //stores candidates
	//int nCandidates; // # of candidates


	//if (isSolution())//base case
		//processSolution(correctValues, currcorrval); //set finished to true, print the board - we are done
	//FINDING MOST ATTRACTIVE SQUARE

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
			edgerow += 3;
		if (i == 6 || i == 7 || i == 8)
			edgerow += 6;
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
			if (sudokuBoard.contents[i][j] == 0)//if spot in row is 0, add to 0 counter for row
				rowcount++;
			if (sudokuBoard.contents[j][i] == 0)
				colcount++;
			if (clusterArray[j] == 0)
				cluscount++;
		}
		rowzeros[i] = rowcount;//i.e. set row [1] to rowcount of row 1 
		cout << "rowcount " << i << " " << rowcount << endl;
		colzeros[i] = colcount;
		cout << "colcount " << i << " " << colcount << endl;
		clusterzeros[i] = cluscount;
		cout << "cluscount " << i << " " << cluscount << endl;
	}
	//END GET AND STORE TOTAL ZEROS FOR ROW, COLUMN, AND CLUSTER
	//BEGIN FIND 0 SQUARE WITH LEAST ZERO VALUE
	int minzeros = 81;//initialize min zeros
	LocationonBoard bestSquare;//initialize best square
	int cluster = 0;//cluster tracker
	
	for (int k = 0; k < 9; k++)//outer loop, loop through board rows
	{
		if ((k != 0) && ((k % 3) == 0))//edge tracking for cluster
			cluster += 3;

		for (int h = 0; h < 9; h++)//innter loop, loop through board columns
		{
			if (h != 0 && h % 3 == 0)//edge tracking for cluster
				cluster++;
			cout << cluster;

			int totalzeros = 0;//initialize total zeros counter
			int samezeros = 0;//initialze same zeros counter (to not double count 0s from the same cluster, if in the same row/col)
			if (sudokuBoard.contents[k][h] == 0)//if the spot on the board is a zero
			{
				if ((h + 4) % 3 == 1)//get same zeros
				{
					if (sudokuBoard.contents[k][h+1] == 0)
						samezeros++;
					if (sudokuBoard.contents[k][h+2] == 0)
						samezeros++;
				}
				else if ((h + 4) % 3 == 2)//get same zeros
				{
					if (sudokuBoard.contents[k][h + 1] == 0)
						samezeros++;
					if (sudokuBoard.contents[k][h - 1] == 0)
						samezeros++;
				}
				else//get same zeros
				{
					if (sudokuBoard.contents[k][h - 1] == 0)
						samezeros++;
					if (sudokuBoard.contents[k][h - 2] == 0)
						samezeros++;
				}
				if ((k + 4) % 3 == 1)//get same zeros
				{
					if (sudokuBoard.contents[k + 1][h] == 0)
						samezeros++;
					if (sudokuBoard.contents[k + 2][h] == 0)
						samezeros++;
				}
				else if ((k + 4) % 3 == 2)//get same zeros
				{
					if (sudokuBoard.contents[k + 1][h] == 0)
						samezeros++;
					if (sudokuBoard.contents[k - 1][h] == 0)
						samezeros++;
				}
				else//get same zeros
				{
					if (sudokuBoard.contents[k - 1][h] == 0)
						samezeros++;
					if (sudokuBoard.contents[k - 2][h] == 0)
						samezeros++;
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
		cout << endl;
		cluster = cluster - 2;
	}
	cout << "The best square is " << bestSquare.x << ", " << bestSquare.y;
	cout << "\nIt has " << minzeros << " zeros in other rows, columns and clusters.";
	print();
}
													 
													 
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


/*
Description: Checks if the board is a solution
*/

bool SudokuSolver::isSolution()
{
	
	if (sudokuBoard.openSquares != 0)
	{
		cout << "OpenSquares is more than 0, returning false";
		return false;
	}
	else
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
			
			if (i == 3 || i == 4 || i ==5)
				edgerow += 3;
			if (i == 6 || i == 7 || i == 8)
				edgerow += 6;
			int val = 0;
			int clusterArray[9] = { 0,0,0,0,0,0,0,0,0 };
			for (int m = 0; m < 3; m++)
			{
				for (int p = 0; p < 3; p++)
				{
					clusterArray[val] = sudokuBoard.contents[m + edgerow][p+edgecol];//copying current cluster into flat cluster Array
					cout << sudokuBoard.contents[m + edgerow][p+edgecol];
					val++;
				}
				cout << endl;
			}
		
			for (int j = 0; j < 9; j++)//process through row, column and cluster  - inner of nest loop
			{
				rowbank[sudokuBoard.contents[i][j] - 1] = sudokuBoard.contents[i][j];//put value found in row[j] into empty row vector spot j
				colbank[sudokuBoard.contents[j][i] - 1] = sudokuBoard.contents[j][i];//put value found in column[j] into empty column vector spot j
				clusterbank[clusterArray[j] - 1] = clusterArray[j];//put value found in clustArrray[j] into empty cluster vector
			}

			for (int z = 0; z < 9; z++)//loop through bank vectors
			{
				if (rowbank[z] != z + 1 || colbank[z] != z + 1 || clusterbank[z] != z + 1)//i.e. if rowbank spot 2 doesn't = 2, or columnbank spot 2 doesn't = 2, or rowbanks spot 2 doesn't = 2
				{
					cout << "I is: " << i << endl;
					cout << z << endl;
					cout << rowbank[z] << " " << colbank[z] << " " << clusterbank[z];
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
void SudokuSolver::makeMove(int correctValues[], int currCorrVal)
{
	int correctRow = sudokuBoard.corrLoStor[currCorrVal].x;
	int correctCol = sudokuBoard.corrLoStor[currCorrVal].y;
	sudokuBoard.contents[correctRow][correctCol] = correctValues[currCorrVal];

}


/*
Description:
*/
void SudokuSolver::unmakeMove(int correctValues[], int currCorrVal)
{
	int correctRow = sudokuBoard.corrLoStor[currCorrVal].x;
	int correctCol = sudokuBoard.corrLoStor[currCorrVal].y;
	sudokuBoard.contents[correctRow][correctCol] = 0;
}
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
