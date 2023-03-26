#include <iostream>
#include <math.h>
#include "triangle.h"


Triangle::Triangle(double a1, double b1, double c1)
{
	a = a1;
	b = b1;
	c = c1;
}

bool Triangle::exst_tr()
{	
	return a + b > c && a + c > b && b + c > a;
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