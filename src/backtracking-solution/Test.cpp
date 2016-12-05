//Test file.
#include<iostream>
#include"SudokuSolver.hpp"
#include<string>


using namespace std;



int main()
{
	int array[81];
	int dummy = 0;
	SudokuSolver easyboard("C:\\Users\\do_de\\OneDrive\\Documents\\minzeros2.txt");
	//easyboard.print();
	easyboard.isSolution();
	//easyboard.solvePuzzle();
	easyboard.backtrack(array, dummy);

	
	system("pause");

	return 0;
}