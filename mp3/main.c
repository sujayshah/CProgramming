#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Introductory Paragraph
   ----------------------
   This code emulates the function of a low pass filter by approximating an output response to an input signal using a finite difference equation in place of a second
   order differential equation. The first and last test inputs give the best response, whereas, the second one does not attenuate the signal as well. In order to 
   compute the output, I split the equation provided into smaller components and combined them at the end.
*/

int main()
{
	double omega1, omega2, omegac, T, dt;
	int N;

	//Scan the inputs from the user.
	scanf("%lf %lf %lf", &omega1, &omega2, &omegac);
	
	T = 3 * 2 * M_PI / omega1;      // Total time
    	N = 20 * T / (2 * M_PI / omega2);   // Total number of time steps
    	dt = T / N;             // Time step

	int i;
	double Voutnew = 0, Voutcur = 0, Voutprev = 0;
	double term1, term2, term3, multiplier;

	//Write your code here!
	for(i = 0; i < N; i++)
	{
		term1 = ((2/(dt*dt*omegac*omegac)) - 1)*Voutcur;
		term2 = ((1/(sqrt(2)*dt*omegac)) - (1/(dt*dt*omegac*omegac)))*Voutprev;
		term3 = (sin(omega1*i*dt)) + (0.5*sin(omega2*i*dt));
		multiplier = 1/((1/(sqrt(2)*dt*omegac)) + (1/(dt*dt*omegac*omegac)));
		Voutnew = multiplier*(term1+term2+term3);
		printf("%lf\n", Voutcur);
		Voutprev = Voutcur;
		Voutcur = Voutnew;
	}


	return 0;
}
