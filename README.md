# sudoku-solver

A simple text-based C++ sudoku solver program that runs in a terminal. It reads in a text file
(see below for file format) and provides a simple solution to the user, output in a separate
text file.

We have implemented a basic backtracking solution to solve sudoku puzzles.

**Running Current Version**

After cloning the repo, run the following commands in the main directory:

```
$ make
```
After compilation is complete, run the below:
```
$ ./solveSudoku

```

Before pushing a new branch, feel free to run the following script
included in the repo to remove those pesky .o files

```
$ ./cleanUp.sh
```


The below puzzles are included in the tests folder
```
Easy
0 2 0 4 5 6 7 8 9
4 5 7 0 8 0 2 3 6
6 8 9 2 3 7 0 4 0
0 0 5 3 6 2 9 7 4
2 7 4 0 9 0 6 5 3
3 9 6 5 7 4 8 0 0
0 4 0 6 1 8 3 9 7
7 6 1 0 4 0 5 2 8
9 3 8 7 2 5 0 6 0

Medium
0 0 8 0 0 0 5 0 0
5 0 4 9 2 8 0 0 6
9 0 3 0 6 5 7 2 0
0 4 9 5 0 6 0 8 1
0 6 0 0 0 0 0 7 0
8 0 0 7 1 2 0 6 9
1 0 0 3 0 0 0 0 2
4 0 0 0 9 0 0 0 3
0 9 0 0 0 4 8 0 0

Hard
8 6 7 0 0 5 0 0 0
0 5 0 0 0 0 0 3 0
0 0 0 1 0 0 0 2 0
1 7 5 0 0 0 8 0 0
0 3 0 6 0 0 0 0 0
0 0 0 2 0 0 0 4 0
0 0 0 9 3 0 0 1 4
0 0 0 0 8 1 0 0 0
0 0 0 0 0 0 2 0 9

Expert
0 0 6 0 0 0 9 0 0
0 0 0 4 0 0 0 7 0
3 0 0 0 2 0 0 0 0
0 1 9 7 0 0 5 0 0
0 7 0 0 0 0 0 0 1
2 0 0 0 9 0 0 0 3
0 0 8 9 0 3 0 4 0
4 0 0 0 5 0 0 0 9
0 0 0 0 0 8 0 0 5

```
