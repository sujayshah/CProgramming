#include <stdio.h>
#include "prime.h"

int main() 
{
	int number;
	int j;
	int result;

	printf("Enter a number: "); // gets input from user
    	scanf("%d", &number); // assigns input to variable 'number'
	
	printf("Printing primes less than or equal to %d:\n", number);

	for(j = 2; j <= number; j++)
	{
		result = is_prime(j);
		if(result == 1)
		{
			printf("%d, ", j);
		}		
	}	

	return 0;
}
