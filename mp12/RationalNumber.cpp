#include "RationalNumber.h"

/* INTRODUCTORY PARAGRAPH
 * ----------------------
 * In this class, I implemented functions to add, subtract, multiply and divide a rational number with either another rational number; a real number or a complex number. For each of these,     
 * depending on the type of the second operand, relevant functions for the particular class relating to that type would be called. This was made possible through inheritance. For example, 
 * operating on real numbers involved calling the 'get_value' function. Similarly, operating on complex numbers involved using the 'get_realComponent' and 'get_imagComponent' functions.
*/

//to_String converts numerator and denominator to string of type num/denom
string RationalNumber::to_String(void)
{
	stringstream my_output;
	my_output << numerator << "/" << denominator;
	return my_output.str();
}

RationalNumber::RationalNumber()
{
	numerator = 0;
	denominator = 0;
	NumberType = 0;
}

RationalNumber::RationalNumber(int numer, int denom)
{
	numerator = numer;
	denominator = denom;
	NumberType = RATIONAL;
}

void RationalNumber::set_numerator(int numer)
{
	numerator = numer;
}

void RationalNumber::set_denominator(int denom)
{
	denominator = denom;
}

int RationalNumber::get_numerator(void) const
{
	return numerator;
}

int RationalNumber::get_denominator(void) const
{
	return denominator;
}

void RationalNumber::set_value (int numer, int denom)
{
	numerator = numer;
	denominator = denom;
}

int RationalNumber::gcd(int a, int b)
{
	while(a != b)
	{
		if(a > b)
		{
			a = a - b;
		}
		else
		{
			b = b - a;
		}
	}
	return a;
}

double RationalNumber::magnitude()
{
	return abs(get_numerator()/get_denominator());	
}	

double RationalNumber::decimal_value() const
{
	return ((double) get_numerator())/((double)get_denominator());
}

RationalNumber RationalNumber::operator + (const RationalNumber& arg)
{
	int newNum = get_numerator()*arg.get_denominator() + arg.get_numerator()*get_denominator();	
	int newDen = get_denominator()*arg.get_denominator();
	int divisor = gcd(newNum, newDen);
	return RationalNumber(newNum/divisor, newDen/divisor);
}

RationalNumber RationalNumber::operator - (const RationalNumber& arg)
{
	int newNum = get_numerator()*arg.get_denominator() - arg.get_numerator()*get_denominator();	
	int newDen = get_denominator()*arg.get_denominator();
	int divisor = gcd(newNum, newDen);
	return RationalNumber(newNum/divisor, newDen/divisor);
}

RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
	int newNum = get_numerator()*arg.get_numerator();
	int newDen = get_denominator()*arg.get_denominator();
	int divisor = gcd(newNum, newDen);
	return RationalNumber(newNum/divisor, newDen/divisor);
}

RationalNumber RationalNumber::operator / (const RationalNumber& arg)
{
	int newNum = get_numerator()*arg.get_denominator();
	int newDen = get_denominator()*arg.get_numerator();
	int divisor = gcd(newNum, newDen);
	return RationalNumber(newNum/divisor, newDen/divisor);
}
		
ComplexNumber RationalNumber::operator + (const ComplexNumber& arg)
{
	double newReal = decimal_value() + arg.get_realComponent();
	return ComplexNumber(newReal, arg.get_imagComponent());
}

ComplexNumber RationalNumber::operator - (const ComplexNumber& arg)
{
	double newReal = decimal_value() - arg.get_realComponent();
	return ComplexNumber(newReal, -1*arg.get_imagComponent());
}

ComplexNumber RationalNumber::operator * (const ComplexNumber& arg)
{
	double newReal = decimal_value()*arg.get_realComponent();
	double newImag = decimal_value()*arg.get_imagComponent();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber RationalNumber::operator / (const ComplexNumber& arg)
{
	ComplexNumber conj(arg.get_realComponent(), -1*arg.get_imagComponent());
	ComplexNumber num(decimal_value()*conj.get_realComponent(), decimal_value()*conj.get_imagComponent());
	RealNumber den(pow(arg.get_realComponent(), 2) + pow(arg.get_imagComponent(), 2));                                                                  
	ComplexNumber result = num/den;
	return result;
}

RealNumber RationalNumber::operator + (const RealNumber& arg)
{
	return RealNumber(arg.get_value() + decimal_value());
}

RealNumber RationalNumber::operator - (const RealNumber& arg)
{
	return RealNumber(decimal_value() - arg.get_value());
}

RealNumber RationalNumber::operator * (const RealNumber& arg)
{
	return RealNumber(decimal_value()*arg.get_value());
}

RealNumber RationalNumber::operator / (const RealNumber& arg)
{
	return RealNumber(decimal_value()/arg.get_value());
}

