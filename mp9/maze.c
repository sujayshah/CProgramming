#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* INTRODUCTORY PARAGRAPH
 * ----------------------
 * This MP finds the solution to a maze using the Depth-First Search (DFS) algorithm in conjunction with the Manhattan Heuristic. The main solving function works by taking an input row and column
 * as the starting point. It then checks the Manhattan distances of all the adjacent points. Based on these distances, the function will perform recursive calls to search for a solution in 
 * different directions beginning with the direction corresponding to the smallest distance. If a direction is valid, we keep going until the base case is reached and we are at the end. Otherwise,
 * the point is marked as visited and we backtrack. The 'create maze' and 'destroy maze' functions use the structure provided in the header file, along with dynamic memory allocation, to store the
 * values from an input text file within an instance of the given structure. Finally, we have 'print maze,' which simply displays the maze onto the screen.
*/


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	int i, j, x;

	FILE *myFile;

	myFile = fopen(fileName, "r");

	maze_t * myMaze = malloc(sizeof(maze_t)); //allocate memory for structure
	
	fscanf(myFile, "%d %d\n", &(myMaze->width), &(myMaze->height)); //set width and height parameters in structure
 
	myMaze->cells = (char**)malloc(myMaze->height*sizeof(char*)); //allocate memory for pointer array

	for(x = 0; x < myMaze->height; x++)
	{
		myMaze->cells[x] = (char*)malloc(myMaze->width*sizeof(char)); //allocate memory for pointers to rows
	}
 
	char newChar;

	for (i = 0; i < myMaze->height; i++)
	{
        	for (j = 0; j < myMaze->width + 1; j++)
           	{
			newChar = fgetc(myFile);

			if(newChar != '\n')
			{	
				myMaze->cells[i][j] = newChar; //fill in the cells

				if(myMaze->cells[i][j] == 'S') //identify start position
				{
					myMaze->startColumn = j; 
					myMaze->startRow = i;
				}
				if(myMaze->cells[i][j] == 'E') //identify end position
				{
					myMaze->endColumn = j;
					myMaze->endRow = i;
				}
			}
		}	 	
	}

	fclose(myFile);	
	
	return myMaze;
}	

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
	int x;

	for(x = 0; x < maze->height; x++)
	{
		free(maze->cells[x]);
	}
	
	free(maze->cells);
	
	free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
	int i, j; 

	for(i = 0; i < maze->height; i++)
	{
		for(j = 0; j < maze->width; j++)
		{
			printf("%c", maze->cells[i][j]);
		}
		printf("\n");
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
	int a, b, c, d, m_dist1, m_dist2, m_dist3, m_dist4, i;

	if(col < 0 || row < 0 || col >= maze->width || row >= maze->height) //out of bounds
	{
		return 0;
	}
	if(maze->cells[row][col] == '%' || maze->cells[row][col] == '~' || maze->cells[row][col] == '.') //invalid point	
	{	
		return 0;
	}
	if(maze->cells[row][col] == 'E') //base case
	{
		return 1;	
	}
	
	maze->cells[row][col] = '.'; //part of solution
	
	a = row + 1; //down
	b = row - 1; //up
	c = col + 1; //right
	d = col - 1; //left

	m_dist1 = abs(maze->endRow - a) + abs(maze->endColumn - col);
	m_dist2 = abs(maze->endRow - b) + abs(maze->endColumn - col);
	m_dist3 = abs(maze->endRow - row) + abs(maze->endColumn - c);
	m_dist4 = abs(maze->endRow - row) + abs(maze->endColumn - d);

	for(i = 0; i < 4; i++)
	{
		if(m_dist1 <= m_dist2 && m_dist1 <= m_dist3 && m_dist1 <= m_dist4) //check which distance is the smallest
		{			
			if(solveMazeManhattanDFS(maze, col, a) == 1)
			{
				maze->cells[maze->startRow][maze->startColumn] = 'S'; //reset the start position as this will have been overwritten by '.'				
				return 1;
			}
			m_dist1 = 1000; //set the smallest distance to some large number so it fails the subsequent conditions and will always be larger than the others
		}
		if(m_dist2 <= m_dist1 && m_dist2 <= m_dist3 && m_dist2 <= m_dist4)
		{		
			if(solveMazeManhattanDFS(maze, col, b) == 1)
			{
				maze->cells[maze->startRow][maze->startColumn] = 'S';
				return 1;
			}
			m_dist2 = 1000;			
		}
		if(m_dist3 <= m_dist1 && m_dist3 <= m_dist2 && m_dist3 <= m_dist4)
		{		
			if(solveMazeManhattanDFS(maze, c, row) == 1)
			{
				maze->cells[maze->startRow][maze->startColumn] = 'S';
				return 1;
			}
			m_dist3 = 1000;	
		}
		if(m_dist4 <= m_dist1 && m_dist4 <= m_dist2 && m_dist4 <= m_dist3)
		{
			if(solveMazeManhattanDFS(maze, d, row) == 1)
			{
				maze->cells[maze->startRow][maze->startColumn] = 'S';
				return 1;
			}
			m_dist4 = 1000;
		}
	}		 
	
	maze->cells[row][col] = '~'; //cell visited

	return 0; //no solution found from here
}
