#include "RealNumber.h"

/* INTRODUCTORY PARAGRAPH
 * ----------------------
 * In this class, I implemented functions to add, subtract, multiply and divide a real number with either another real number; a complex number or a rational number. For each of these, depending 
 * on the type of the second operand, relevant functions for the particular class relating to that type would be called. This was made possible through inheritance. For example, operating on 
 * complex numbers involved calling the 'get_realComponent' and 'get_imagComponent' functions. Similarly, operating on rational numbers involved using the 'decimal_value' function.
*/


//to_String converts real and imaginary components to string of type a+bi
string RealNumber::to_String(void)
{
	stringstream my_output;
	my_output << value;
	return my_output.str();
}

RealNumber::RealNumber()
{
	value = 0;
	NumberType = 0;
}

RealNumber::RealNumber(double rval)
{
	value = rval;
	NumberType = REAL;
}

void RealNumber::set_value(double rval)
{
	value = rval;
}

double RealNumber::get_value(void) const
{
	return value;
}

double RealNumber::magnitude()
{
	return abs(value);
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
	double newVal = get_value() + arg.get_value();
	return RealNumber(newVal);
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
	double newVal = get_value() - arg.get_value();
	return RealNumber(newVal);
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
	double newVal = get_value()*arg.get_value();
	return RealNumber(newVal);
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
	double newVal = get_value()/arg.get_value();
	return RealNumber(newVal);
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg)
{
	double newReal = get_value() + arg.get_realComponent();
	return ComplexNumber(newReal, arg.get_imagComponent());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg)
{
	double newReal = get_value() - arg.get_realComponent();
	return ComplexNumber(newReal, -1*arg.get_imagComponent());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg)
{
	double newReal = get_value()*arg.get_realComponent();
	double newImag = get_value()*arg.get_imagComponent();
	return ComplexNumber(newReal, newImag);
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg)
{
	ComplexNumber conj(arg.get_realComponent(), -1*arg.get_imagComponent());
	ComplexNumber num(get_value()*conj.get_realComponent(), get_value()*conj.get_imagComponent());
	RealNumber den(pow(arg.get_realComponent(), 2) + pow(arg.get_imagComponent(), 2));                                                                  
	ComplexNumber result = num/den;
	return result;
}

RealNumber RealNumber::operator + (const RationalNumber& arg)
{
	RealNumber num(get_value()*arg.get_denominator() + arg.get_numerator());
	RealNumber result(num.get_value()/arg.get_denominator());
	return result;
}

RealNumber RealNumber::operator - (const RationalNumber& arg)
{
	RealNumber num(get_value()*arg.get_denominator() - arg.get_numerator());
	RealNumber result(num.get_value()/arg.get_denominator());
	return result;
}

RealNumber RealNumber::operator * (const RationalNumber& arg)
{
	RealNumber num(get_value()*arg.get_numerator());
	RealNumber result(num.get_value()/arg.get_denominator());
	return result;
}

RealNumber RealNumber::operator / (const RationalNumber& arg)
{
	RealNumber num(get_value()*arg.get_denominator());
	RealNumber result(num.get_value()/arg.get_numerator());
	return result;
}

