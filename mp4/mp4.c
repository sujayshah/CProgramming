#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


double fx_val(double a, double b, double c, double d, double e, double x)
{
	// Evaluate polynomial at x

	double result;	

	result = (a*pow(x, 4)) + (b*pow(x, 3)) + (c*pow(x, 2)) + (d*x) + e;

	return result;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
	// Evaluate first derivative of polynomial at x
	
	double result_prime;
	
	result_prime = (4*a*pow(x, 3)) + (3*b*pow(x, 2)) + (2*c*x) + d;
	
	return result_prime;   
}


double fx_ddval(double a, double b, double c, double d, double e, double x)
{
	// Evaluate second derivative of polynomial at x

	double result_double_prime;

	result_double_prime = (12*a*pow(x, 2)) + (6*b*x) + (2*c);

	return result_double_prime;
}

double double_abs(double x)
{
	if(x >= 0)
	{
		return x;
	}
	else
	{
		x = x*-1;
		return x;
	}
}

double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
	// Determine root from the starting point x

	int loop_count = 0;
	double x_next, numerator, denominator, difference, mag_diff;	

	while(loop_count != 10000)
	{
		numerator = 2*fx_val(a, b, c, d, e, x)*fx_dval(a, b, c, d, e, x);
		denominator = (2*pow(fx_dval(a, b, c, d, e, x), 2)) - (fx_val(a, b, c, d, e, x)*fx_ddval(a, b, c, d, e, x));
		x_next = x - (numerator/denominator);	
		difference = x_next - x;
		mag_diff = double_abs(difference);
		if(mag_diff <= 0.000001)
		{
			return x_next;
			break;
		}
		x = x_next;
		loop_count++;
	}	

	printf("No roots found.");
	return 1000000;             // Set non-root return value to some very high number to avoid conflict if a root is found at 0
}




int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    
	// Compute sign changes in p(x + l)

	double a1, b1, c1, d1, e1;
	int count_l, count_r, upper_bound;

	count_l = 0;
	count_r = 0; 	

	a1 = a;
	b1 = (4*a*l) + b;
	c1 = (6*a*pow(l, 2)) + (3*b*l) + c;
	d1 = (4*a*pow(l, 3)) + (3*b*pow(l, 2)) + (2*c*l) + d;
	e1 = (a*pow(l, 4)) + (b*pow(l, 3)) + (c*pow(l, 2)) + (d*l) + e;  

	if(a1 >= 0)
	{
		if(b1 < 0)
		{
			count_l++;
		}
	}
	else
	{
		if(b1 >= 0)
		{
			count_l++;
		}
	}

	if(b1 >= 0)
	{
		if(c1 < 0)
		{
			count_l++;
		}
	}
	else
	{
		if(c1 >= 0)
		{
			count_l++;
		}
	}

	if(c1 >= 0)
	{
		if(d1 < 0)
		{
			count_l++;
		}
	}
	else
	{
		if(d1 >= 0)
		{
			count_l++;
		}
	}

	if(d1 >= 0)
	{
		if(e1 < 0)
		{
			count_l++;
		}
	}	
	else
	{
		if(e1 >= 0)
		{
			count_l++;
		}
	}		

	// Compute sign changes in p(x + r)

	double a2, b2, c2, d2, e2;	

	a2 = a;
	b2 = (4*a*r) + b;
	c2 = (6*a*pow(r, 2)) + (3*b*r) + c;
	d2 = (4*a*pow(r, 3)) + (3*b*pow(r, 2)) + (2*c*r) + d;
	e2 = (a*pow(r, 4)) + (b*pow(r, 3)) + (c*pow(r, 2)) + (d*r) + e;  

	if(a2 >= 0)
	{
		if(b2 < 0)
		{
			count_r++;
		}
	}	
	else
	{
		if(b2 >= 0)
		{
			count_r++;
		}
	}

	if(b2 >= 0)
	{
		if(c2 < 0)
		{
			count_r++;
		}
	}	
	else
	{
		if(c2 >= 0)
		{
			count_r++;
		}
	}

	if(c2 >= 0)
	{
		if(d2 < 0)
		{
			count_r++;
		}
	}	
	else
	{
		if(d2 >= 0)
		{
			count_r++;
		}
	}

	if(d2 >= 0)
	{
		if(e2 < 0)
		{
			count_r++;
		}
	}	
	else
	{
		if(e2 >= 0)
		{
			count_r++;
		}
	}

	// Determine the upper bound

	upper_bound = abs(count_l - count_r);	

	if(upper_bound == 0)
	{
		printf("The polynomial has no roots in the given interval.");
		return 0;	
	}
	else
	{	
		return upper_bound;
	}
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) 
	{
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
    
    	// Primary root finding function

	double x = l;
	int max_roots = rootbound(a, b, c, d, e, r, l);
	double root;

	if(max_roots == 0)
	{
		exit(0);
 	}

	while(x <= r)
	{
		root = newrfind_halley(a, b, c, d, e, x);
		if(root != 1000000)
		{
			printf("Root found: %lf\n", root);
		}
		x = x + 0.5;
	}
    
    	fclose(in);
    
    	return 0;
}
