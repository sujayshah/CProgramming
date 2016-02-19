#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


double fx_val(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the polynomial at the value x
    return 0;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the derivative of the polynomial at the value x
    return 0;
   
}


double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x
    return 0;
}

double double_abs(double x)
{
    //Change this to return the absolute value of the double value x
    return 0;
}

double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x
    return 0;
}




int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    
    //Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)
    return 0;
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
    
    //Write the code to call the appropriate functions and perform the task described in the writeup.
    
    
    fclose(in);
    
    return 0;
}
