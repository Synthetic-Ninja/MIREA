#include <iostream>
#include <math.h>
#include <math.h>
#include "triangle.h"


bool Triangle::exst_tr()
{	
	return a + b > c && a + c > b && b + c > a;
}

void Triangle::set(double a1, double b1, double c1)
{
	a = a1;
	b = b1;
	c = c1;
}

void Triangle::show()
{
	std::cout << "A=" << a << " " << "B=" << b << " " << "C=" << c << std::endl; 
}

double Triangle::perimetr()
{
	return a + b + c;
}

double Triangle::square()
{
 double p = perimetr() / 2;

 return pow(p*(p - a)*(p - b)*(p - c),0.5);
}