# sudoku-solver

A simple text-based C++ sudoku solver program that runs in a terminal. It reads in a text file
(see below for file format) and provides a simple solution to the user, output in a separate
text file.

We have implemented a basic backtracking solution to solve sudoku puzzles.

**Running Current Version**

After cloning the repo, run the following commands in the main directory:

```
make

./solveSudoku

```

There is currently one test case, which may be found in the tests folder.


The current board being tested is listed below:

0 2 0 4 5 6 7 8 9
4 5 7 0 8 0 2 3 6
6 8 9 2 3 7 0 4 0
0 0 5 3 6 2 9 7 4
2 7 4 0 9 0 6 5 3
3 9 6 5 7 4 8 0 0
0 4 0 6 1 8 3 9 7
7 6 1 0 4 0 5 2 8
9 3 8 7 2 5 0 6 0
