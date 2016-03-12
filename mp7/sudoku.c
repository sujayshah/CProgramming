#include "sudoku.h"

/* INTRODUCTORY PARAGRAPH
 * ----------------------
 * This MP solves a sudoku puzzle using a recursive backtracking algorithm. The main solve function parses through each of the cells in the grid in order to find an empty cell. If one is not found, the puzzle has been solved and we are 
 * done. In the case that we do find an empty cell, we loop through all numbers from 1-9 that can be stored within it and check if any of them are valid. If we reach a point where none of the numbers can be used to fill that cell, we 
 * reset its value and backtrack to the previous solution. We can verify the validity of a number by going through each element in the row and column to which we want to assign that number and ensuring that the value does not already
 * exist. In addition, we need to check the 3x3 grid of that particular cell to ensure that the value is not contained within it either. This process is repeated until we have a complete solution.
*/

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// Start coding your MP here.
// ------------------------------------------------------------------------------------------------

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) 
{

  assert(i>=0 && i<9);

  // BEG TODO

	for(int x = 0; x < 9; x++)
	{
		if(sudoku[i][x] == val)
		{
			return 1;
		}
	}		
  	return 0;

  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) 
{

  assert(j>=0 && j<9);

  // BEG TODO

	for(int x = 0; x < 9; x++)
	{
		if(sudoku[x][j] == val)
		{
			return 1;
		}
	}
  	return 0;

  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) 
{
   
  assert(i>=0 && i<9);
  
  // BEG TODO

	int row = (i/3)*3;
	int column = (j/3)*3;

	int x, y;
	
	for(x = 0; x < 3; x++)
	{
		for(y = 0; y < 3; y++)
		{
			if(sudoku[row + x][column + y] == val)
			{
				return 1;
			}
		}
	}
	return 0;
 
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) 
{

  // BEG TODO.

	int a, b, c;

	a = is_val_in_row(val, i, sudoku);
	b = is_val_in_col(val, j, sudoku);
	c = is_val_in_3x3_zone(val, i, j, sudoku);

  	if(a == 0 && b == 0 && c == 0)
	{
		return 1; //val can be used
	}
	else
	{
		return 0; //val cannot be used
	}

  // END TODO.
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) 
{

  // BEG TODO.

	int i, j, flag;

	for(int x = 0; x < 9; x++)
	{
		for(int y = 0; y < 9; y++)
		{
			if(sudoku[x][y] == 0)
			{
				i = x;
				j = y;
				flag = 1; //flag indicates that this statement has been executed and an empty cell was found
			}
		}
	}
	
	if(flag != 1)
	{
		return 1; //all cells have been assigned
	}

	for(int num = 1; num < 10; num++)
	{
		int z = is_val_valid(num, i, j, sudoku);

		if(z == 1)
		{
			sudoku[i][j] = num;
			
			if(solve_sudoku(sudoku) == 1)
			{
				return 1;
			}

			sudoku[i][j] = 0;
		}
	}
	return 0;
  
  // END TODO.
}



