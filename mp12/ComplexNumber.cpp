#include "ComplexNumber.h"

/* INTRODUCTORY PARAGRAPH
 * ----------------------
 * In this class, I implemented functions to add, subtract, multiply and divide a complex number with either another complex number; a real number or a rational number. For each of these,     
 * depending on the type of the second operand, relevant functions for the particular class relating to that type would be called. This was made possible through inheritance. For example, 
 * operating on real numbers involved calling the 'get_value' function. Similarly, operating on rational numbers involved using the 'decimal_value' function.
*/

//to_String converts real and imaginary components to string of type a+bi
string ComplexNumber::to_String(void)
{
	stringstream my_output;
	my_output << realComponent;
	if(imagComponent >= 0)
	{
		my_output << " + " << imagComponent << "i";
	}
	else if(imagComponent < 0)
	{
		my_output << "-" << imagComponent*(-1) << "i";
	}
	return my_output.str();
}

ComplexNumber::ComplexNumber()
{
	realComponent = 0;
	imagComponent = 0;
	NumberType = 0;
}

ComplexNumber::ComplexNumber(double real, double imag)
{
	realComponent = real;
	imagComponent = imag;
	NumberType = COMPLEX;
}

void ComplexNumber::set_realComponent(double rval)
{
	realComponent = rval;
}

void ComplexNumber::set_imagComponent(double ival)
{
	imagComponent = ival;
}

double ComplexNumber::get_realComponent(void) const
{
	return realComponent;
}

double ComplexNumber::get_imagComponent(void) const
{
	return imagComponent;
}

void ComplexNumber::set_value (double rval, double ival)
{
	realComponent = rval;
	imagComponent = ival;
}

double ComplexNumber::magnitude()
{
	return sqrt(pow(realComponent, 2) + pow(imagComponent, 2));		
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
	double newReal = get_realComponent() + arg.get_realComponent();
	double newImag = get_imagComponent() + arg.get_imagComponent();
	return ComplexNumber(newReal, newImag);
}	

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
	double newReal = get_realComponent() - arg.get_realComponent();
	double newImag = get_imagComponent() - arg.get_imagComponent();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
	double newReal = get_realComponent()*arg.get_realComponent() - get_imagComponent()*arg.get_imagComponent();
	double newImag = get_realComponent()*arg.get_imagComponent() + get_imagComponent()*arg.get_realComponent();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
	double denom = pow(arg.get_realComponent(), 2) + pow(arg.get_imagComponent(), 2);
	double realNum = get_realComponent()*arg.get_realComponent() + get_imagComponent()*arg.get_imagComponent(); 
	double imagNum = get_imagComponent()*arg.get_realComponent() - get_realComponent()*arg.get_imagComponent();
	return ComplexNumber(realNum/denom, imagNum/denom);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
	double newReal = get_realComponent() + arg.get_value();
	return ComplexNumber(newReal, get_imagComponent());
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
	double newReal = get_realComponent() - arg.get_value();
	return ComplexNumber(newReal, get_imagComponent());
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
	double newReal = get_realComponent()*arg.get_value();
	double newImag = get_imagComponent()*arg.get_value();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
	double newReal = get_realComponent()/arg.get_value();
	double newImag = get_imagComponent()/arg.get_value();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber ComplexNumber::operator + (const RationalNumber& arg)
{
	double newReal = get_realComponent() + arg.decimal_value();
	return ComplexNumber(newReal, get_imagComponent());
}

ComplexNumber ComplexNumber::operator - (const RationalNumber& arg)
{
	double newReal = get_realComponent() - arg.decimal_value();
	return ComplexNumber(newReal, get_imagComponent());
}

ComplexNumber ComplexNumber::operator * (const RationalNumber& arg)
{
	double newReal = get_realComponent()*arg.decimal_value();
	double newImag = get_imagComponent()*arg.decimal_value();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber ComplexNumber::operator / (const RationalNumber& arg)
{
	double newReal = get_realComponent()/arg.decimal_value();
	double newImag = get_imagComponent()/arg.decimal_value();
	return ComplexNumber(newReal, newImag);
}		

