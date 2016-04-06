#include <stdio.h>

int findpair(int array[], int start, int end);
int main(){
	int N1 = 8, N2= 11, N3 = 7;
	int array1[] = {5, 7, 3, 3, 24, 12, 24, 19};
	int array2[] = {29, 35, 77, 57, 35, 4, 29, 16, 81, 62, 16};
	int array3[] = {16, 13, 25, 16, 1, 10, 16};
	
	printf("%d\n", findpair(array1, 0, 0));
	printf("%d\n", findpair(array1, 0, N1-1));
	printf("%d\n", findpair(array3, 0, N3-1));
	printf("%d\n", findpair(array2, 0, N2-1));
	
	return 0;

}


int findpair(int array[],int start, int end)
{
	int j, occurrences, pairs;

	while(start != end) //base case is when start = end
	{
		if(array[start] == 0) //check if a particular array value has been seen before. If it has, its value will be 0.
		{
			findpair(array, start+1, end); //recall function with incremented start index to check next value
		}
		for(j = 0; j <= end; j++) //value has not been seen before
		{
			if(array[j] == array[start]) //parse array to check for repeats of the value we are currently looking at
			{
				occurrences++; //increment if we find a match
				pairs = occurrences/2; //divide by two to get number of non-overlapping pairs	
			}
		}
		array[start] = 0; //mark number as seen
		findpair(array, start+1, end); //check next value
	}
	if(pairs == 0)
	{
		return 0;
	}
	else
	{
		return pairs;
	}	
}			 




