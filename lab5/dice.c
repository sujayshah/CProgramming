//Function for generating three d6 rolls

#include <stdlib.h>
#include "dice.h"

void roll_three(int* one, int* two, int* three)
{
	*one = rand()%6 + 1; //random number between 1-6
	*two = rand()%6 + 1;
	*three = rand()%6 + 1;
}
