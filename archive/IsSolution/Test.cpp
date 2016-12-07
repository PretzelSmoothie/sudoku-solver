//Test file.
#include<iostream>
#include"SudokuSolver.hpp"
#include<string>


using namespace std;



int main()
{
	int array[81];
	int dummy = 0;
	SudokuSolver easyboard("C:\\Users\\do_de\\OneDrive\\Documents\\zerocheck.txt");
	easyboard.print();
	easyboard.isSolution(array, dummy);
	//easyboard.solvePuzzle();

	
	system("pause");

	return 0;
}