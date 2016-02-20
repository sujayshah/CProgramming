#include "prime.h"

int is_prime(int n) 
{
	int i;
	int remainder;
	
	for(i = 2; i < n; i++)
	{
		remainder = n%i;
		if(remainder == 0)
		{
			return 0; // returned if not prime
			break;
		}
	}
	return 1; // returned if prime
}
