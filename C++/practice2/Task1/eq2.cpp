#include <cmath>
#include <iostream>

#include "eq2.h"


eq2::eq2(double in_a, double in_b, double in_c)
{
	set(in_a, in_b, in_c);
}


void eq2::set(double in_a, double in_b, double in_c)
{
	a = in_a;
	b = in_b;
	c = in_c;
	d = pow(b, 2) - (4 * a * c);
}

double eq2::find_x()
{
	if (d < 0)
	{
		std::cout << "Корней нет" << std::endl;
		return 0;
	}

	if (d == 0)
	{
		double x = -b / (2 * a);
		return x;
	}

	if (d > 0)
	{
		double x1 = (-b - sqrt(d)) / (2 * a);
		double x2 = (-b + sqrt(d)) / (2 * a);
		return x1 > x2? x1 : x2;
	}

}

double eq2::find_y(double x1)
{

 return (a * pow(x1, 2)) + (b * x1) + c;

}


eq2 operator + (eq2& obj1, eq2& obj2)
{
	double a, b, c;
	a = obj1.a + obj2.a;
	b = obj1.b + obj2.b;
	c = obj1.c + obj2.c;

	return eq2(a, b, c);
}


