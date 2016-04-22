#include "Rectangle.h"

//Empty Constructor sets instantiates a rectangle with length and width set as 0
Rectangle::Rectangle()
{
	length = 0;
	width = 0;
}

//Standard Constructor sets instantiates a rectangle with length and width set as input values
Rectangle::Rectangle(int input_length, int input_width)
{
	length = input_length;
	width = input_width;
}

//Setter and Getter functions
void Rectangle::set_length(int input_length)
{
	length = input_length;
}

void Rectangle::set_width(int input_width)
{
	width = input_width;
}

int Rectangle::get_length(void) const
{
	return length;
}

int Rectangle::get_width(void) const
{
	return width;
}

//Calculate Area of rectangle
int Rectangle::area(void)
{
	return length*width;
}

//Calculate Perimeter of rectangle
int Rectangle::perimeter(void)
{
	return 2*length + 2*width;
}

/*Addition operator overload
* We define addition of two rectangles to be as follows: R3 = R1 + R2
* where length of R3 = length R1 + length R2
* and width R3 = max(width R1, width R2)
*/
Rectangle Rectangle::operator + (const Rectangle& other) //a+b, a calls operator with b as argument
{
	int newlength = get_length() + other.get_length();
	int newwidth;

	if(get_width() > other.get_width())
	{
		newwidth = get_width();
	}
	else
	{
		newwidth = other.get_width();
	}

	return Rectangle(newlength, newwidth);
}

/*Multiplication operator overload
* We define addition of two rectangles to be as follows: R3 = R1 * R2
* where length of R3 = length R1 + length R2
* and width R3 = width R1 + width R2
*/
Rectangle Rectangle::operator * (const Rectangle& other)
{
	return Rectangle(get_length() + other.get_length(), get_width() + other.get_width());
}
