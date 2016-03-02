/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
 * INTRODUCTORY PARAGRAPH
 * ----------------------
 * The following code is used to play the codebreaker game. The user enters a seed which generates a random sequence of four numbers. They are then given 12 attempts
 * to guess the correct solution. After making each guess the user is told how many perfect and imperfect matches they got so that they can use this information to 
 * improve upon their prior guess. 
 * The 'set seed' function within this code simply checks if the entered seed is valid and proceeds accordingly. The 'start game' function generates the random 
 * sequence. Finally, the 'make guess' function allows the user to enter an input of 4 integers. It then checks the validity of this input and, if it is valid,
 * compares this to the actual sequence to provide feedback on the matches.
 */

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

int set_seed (const char seed_str[])
{
	int seed;
	char post[2];
	
	if(sscanf(seed_str, "%d%1s", &seed, post) == 1)
	{
		srand(seed);
		return 1;	
	}
	else
	{
		printf("set_seed: invalid seed\n");
		return 0;
	}	 
}

void start_game (int* one, int* two, int* three, int* four)
{
	*one = rand()%8 + 1;
	solution1 = *one;

	*two = rand()%8 + 1;
	solution2 = *two;

	*three = rand()%8 + 1;
	solution3 = *three;

	*four = rand()%8 + 1;
	solution4 = *four;

	guess_number = 1;      
}

int make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
	
	int w, x, y, z;
	char post[2];		
		
	if(sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 4)
	{
		if(w < 9 && x < 9 && y < 9 && z < 9)
		{
			*one = w;
			*two = x;
			*three = y;
			*four = z;

			int paired1, paired2, paired3, paired4;
			paired1 = paired2 = paired3 = paired4 = 0;
			int perfect_matches = 0;
			int misplaced_matches = 0;

			if(w == solution1)
			{
				perfect_matches++;
				paired1 = 1;
			}
			if(x == solution2)
			{
				perfect_matches++;
				paired2 = 1;
			}
			if(y == solution3)
			{
				perfect_matches++;
				paired3 = 1;
			}
			if(z == solution4)
			{
				perfect_matches++;
				paired4 = 1;
			}

			if(paired1 != 1)
			{
				if(w == solution2)
				{
					misplaced_matches++;
				}
				else if(w == solution3)
				{
					misplaced_matches++;
				}
				else if(w == solution4)
				{
					misplaced_matches++;
				}
			}
			if(paired2 != 1)
			{
				if(x == solution1)
				{
					misplaced_matches++;
				}
				else if(x == solution3)
				{
					misplaced_matches++;
				}
				else if(x == solution4)
				{
					misplaced_matches++;
				}
			}
			if(paired3 != 1)
			{
				if(y == solution1)
				{
					misplaced_matches++;
				}
				else if(y == solution2)
				{
					misplaced_matches++;
				}
				else if(y == solution4)
				{
					misplaced_matches++;
				}
			}
			if(paired4 != 1)
			{
				if(z == solution1)
				{
					misplaced_matches++;
				}
				else if(z == solution2)
				{
					misplaced_matches++;
				}
				else if(z == solution3)
				{
					misplaced_matches++;
				}
			}				

			printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_matches, misplaced_matches);
			guess_number++;
		}
		else
		{
			printf("make_guess: invalid guess\n");
			return 0;
		}	
	}
	else
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}
	return 1; 
}


