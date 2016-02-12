#include<stdio.h>
#include<math.h>

int main()
{
	double omega1, omega2, x, f;
	int n;
	printf("Enter n, omega1, omega2:");
	scanf("%d %lf %lf" ,&n,&omega1,&omega2);
	int i;
	for(i=0, i<n, i++)
	{
		x=(i*3.14)/n;
		f=sin(omega1*x)+0.5*sin(omega2*x);
		printf("%lf %lf\n", x, f);
	}
