#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double omega1, omega2, omegac, T, dt;
	int N, method;

	//Scan the inputs from the user.
	scanf("%lf %lf %lf %d", &omega1, &omega2, &omegac, &method);
	
	T = 3 * 2 * M_PI / omega1;      // Total time
    	N = 20 * T / (2 * M_PI / omega2);   // Total number of time steps
    	dt = T / N;             // Time step

	if (method == 1) {
		int i;
		double Voutnew = 0, Voutcur = 0, Voutprev = 0;

		//Write your code here!

	}
	// Method number 2 corresponds to the Runge-Kutta method (only for challenge).
	else if (method == 2) {
		
		//Write your code here for the challenge problem.

		}
	}
	else {
		printf("Incorrect method number.\n");
		return -1;
	}

	return 0;
}
